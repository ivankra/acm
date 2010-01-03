using System;

public class OptimalAssignmentSolver {
    /// <summary>
    /// Solves optimal assignment problem using the Kuhn-Munkres
    /// (aka Hungarian) algorithm. Time complexity: O(n^3).
    /// 
    /// References:
    /// http://www.math.uwo.ca/~mdawes/courses/344/kuhn-munkres.pdf
    /// http://www.ecp6.jussieu.fr/pageperso/bondy/books/gtwa/pdf/chapter5.pdf
    /// </summary>
    /// <param name="a">A square matrix.</param>
    /// <returns>
    /// A permutation p of integers 0, 1, ..., n-1, (where
    /// n is the size of matrix a) such that the expression
    ///   a[0, p[0]] + a[1, p[1]] + ... + a[n-1, p[n-1]]
    /// is maximum possible among all such permutations.
    /// </returns>
    public static int[] KuhnMunkres(int[,] a) {
        int N = a.GetLength(0);
        if (N == 0)
            return new int[0];

        int[] lx = new int[N], ly = new int[N];   // labelling function for vertices in first and second partitions
        int[] mx = new int[N], my = new int[N];   // mx[u]=v, my[v]=u <==> u and v are currently matched;  -1 values means 'not matched'
        int[] px = new int[N], py = new int[N];   // predecessor arrays.  used in DFS to reconstruct paths.
        int[] stack = new int[N];

        // invariant: lx[u] + ly[v] >= a[u, v]
        // (implies that any perfect matching in subgraph containing only
        // edges u, v for which lx[u]+ly[v]=a[u,v] is the optimal matching.)

        // compute initial labelling function:  lx[i] = max_j(a[i, j]), ly[j] = 0;
        for (int i = 0; i < N; i++) {
            lx[i] = a[i, 0];
            for (int j = 0; j < N; j++)
                if (a[i, j] > lx[i]) lx[i] = a[i, j];
            ly[i] = 0;

            mx[i] = my[i] = -1;
        }

        for (int size = 0; size < N;) {
            int s;
            for (s = 0; mx[s] != -1; s++);

            // s is an unmatched vertex in the first partition.
            // At the current iteration we will either find an augmenting path
            // starting at s, or we'll extend the equality subgraph so that
            // such a path will exist at the next iteration.

            for (int i = 0; i < N; i++)
                px[i] = py[i] = -1;
            px[s] = s;

            // DFS
            int t = -1;
            stack[0] = s;
            for (int top = 1; top > 0;) {
                int u = stack[--top];
                for (int v = 0; v < N; v++) {
                    if (lx[u] + ly[v] == a[u, v] && py[v] == -1) {
                        if (my[v] == -1) {
                            // we've found an augmenting path
                            t = v;
                            py[t] = u;
                            top = 0;
                            break;
                        }

                        py[v] = u;
                        px[my[v]] = v;
                        stack[top++] = my[v];
                    }
                }
            }

            if (t != -1) {
                // augment along the found path
                while (true) {
                    int u = py[t];
                    mx[u] = t;
                    my[t] = u;
                    if (u == s) break;
                    t = px[u];
                }
                ++size;
            } else {
                // No augmenting path exists from s in the current equality graph,
                // Modify labelling function a bit...

                int delta = int.MaxValue;
                for (int u = 0; u < N; u++) {
                    if (px[u] == -1) continue;
                    for (int v = 0; v < N; v++) {
                        if (py[v] != -1) continue;
                        int z = lx[u] + ly[v] - a[u, v];
                        if (z < delta)
                            delta = z;
                    }
                }

                for (int i = 0; i < N; i++) {
                    if (px[i] != -1) lx[i] -= delta;
                    if (py[i] != -1) ly[i] += delta;
                }
            }
        }

        // Verify optimality
        bool correct = true;
        for (int u = 0; u < N; u++) {
            for (int v = 0; v < N; v++) {
                correct &= (lx[u] + ly[v] >= a[u, v]);
                if (mx[u] == v)
                    correct &= (lx[u] + ly[v] == a[u, v]);

                if (!correct) {
                    throw new Exception(
                        "*** Internal error: optimality conditions are not satisfied ***\n" +
                        "Most probably an overflow occurred");
                }
            }
        }

        return mx;
    }
}

public class Tester {
    static int DP(int[,] a) {
        int N = a.GetLength(0);
        int[] f = new int[1 << N];
        f[0] = 0;
        for (int mask = 1; mask < (1 << N); mask++) {
            int i = -1;
            for (int k = 0; k < N; k++)
                i += (mask >> k) & 1;

            f[mask] = int.MinValue;
            for (int j = 0; j < N; j++) {
                if ((mask & (1 << j)) != 0) {
                    int t = a[i, j] + f[mask ^ (1 << j)];
                    if (t > f[mask])
                        f[mask] = t;
                }
            }
        }
        return f[(1 << N) - 1];
    }

    static int Hungarean(int[,] a) {
        int[] v = OptimalAssignmentSolver.KuhnMunkres(a);
        int res = 0;
        for (int i = 0; i < a.GetLength(0); i++)
            res += a[i, v[i]];
        return res;
    }

    static int[,] RandomMatrix(int N, Random random) {
        int[,] a = new int[N, N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i, j] = random.Next(1000000);
        return a;
    }

    public static void Main(string[] args) {
        Random random = new Random();
        for (int cs = 1; cs <= 1000; cs++) {
            const int DP_LIMIT = 22;

            int N = random.Next(cs <= 100 ? DP_LIMIT : 100);
            Console.Write("Test {0}: N={1} ", cs, N);
            Console.Out.Flush();

            int[,] mat = RandomMatrix(N, random);
            int hung = Hungarean(mat);
            int dp = (N < DP_LIMIT ? DP(mat) : -1);

            Console.WriteLine("result={0} DP={1}", hung, dp == -1 ? "<not computed>" : dp.ToString());

            if (dp >= 0 && hung != dp) {
                Console.WriteLine("*FAILED*\n");
                return;
            }
        }

        Console.WriteLine("All tests passed.");
    }
}
