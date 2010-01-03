using System;

public class Program
{
    public static int Solve(int N, int M) {
        if (N < M) return Solve(M, N);

        int[,,] a = new int[N+1, M+1, 1<<M];
        a[N, 0, 0] = 1;

        for (int row = N - 1; row >= 0; --row) {
            for (int mask = 0; mask < (1 << M); ++mask)
                a[row, M, mask] = a[row+1, 0, mask];

            for (int col = M - 1; col >= 0; --col) {
                for (int mask = 0; mask < (1 << M); ++mask) {
                    int res;

                    if ((mask & (1 << col)) != 0) {
                        res = a[row, col + 1, mask & ~(1 << col)];
                    } else {
                        res = a[row, col + 1, mask];
                        res += a[row, col + 1, mask | (1 << col)];
                        if ((mask & (3 << col)) == 0 && col + 2 <= M)
                            res += a[row, col + 2, mask];
                    }

                    a[row, col, mask] = res;
                }
            }
        }

        return a[0, 0, 0];
    }

    public static void Main(string[] args) {
        int[] a = Array.ConvertAll<string, int>(Console.ReadLine().Split(' '), int.Parse);
        Console.WriteLine(Solve(a[0], a[1]));
    }
}
