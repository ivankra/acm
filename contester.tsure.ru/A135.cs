using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    int height, width;
    string[] map;
    int[,] cc;

    bool[,] adj;
    int[] color;
    int N;

    int[] dx = new int[] { 1, -1, 0, 0 };
    int[] dy = new int[] { 0, 0, 1, -1 };

    void dfs(int y, int x) {
        for (int i = 0; i < 4; i++) {
            int y1 = y + dy[i];
            int x1 = x + dx[i];
            if (0 <= y1 && y1 < height && 0 <= x1 && x1 < width) {
                if (map[y1][x1] == map[y][x] && cc[y1, x1] == 0) {
                    cc[y1, x1] = cc[y, x];
                    dfs(y1, x1);
                }
                if (map[y1][x1] != map[y][x] && cc[y1, x1] != 0) {
                    adj[cc[y, x], cc[y1, x1]] = true;
                    adj[cc[y1, x1], cc[y, x]] = true;
                }
            }
        }
    }

    int Play(bool ruleB) {
        int[,,,] dist = new int[N+1, 7, N+1, 7];

        Queue<int> Q = new Queue<int>();
        Q.Enqueue(cc[0, 0]);
        Q.Enqueue(color[cc[0, 0]]);
        Q.Enqueue(cc[height - 1, width - 1]);
        Q.Enqueue(color[cc[height - 1, width - 1]]);

        while (Q.Count != 0) {
            int u = Q.Dequeue();
            int uc = Q.Dequeue();
            int v = Q.Dequeue();
            int vc = Q.Dequeue();

            if (u == v || adj[u, v]) {
                int res = dist[u, uc, v, vc];
                return res;
            }

            for (int w = 1; w <= N; w++) {
                for (int wc = 1; wc <= 6; wc++) {
                    if (w != u && wc != color[w]) continue;
                    if (!adj[u, w] || dist[v, vc, w, wc] != 0) continue;
                    if (ruleB && (wc == uc || wc == vc)) continue;

                    dist[v, vc, w, wc] = dist[u, uc, v, vc] + 1;
                    Q.Enqueue(v);
                    Q.Enqueue(vc);
                    Q.Enqueue(w);
                    Q.Enqueue(wc);
                }
            }
        }

        throw new Exception();
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        height = input.NextInt();
        width = input.NextInt();

        map = new string[height];
        for (int i = 0; i < height; i++)
            map[i] = input.Next();

        N = 0;
        adj = new bool[64, 64];
        color = new int[64];
        cc = new int[height, width];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (cc[i, j] == 0) {
                    N++;
                    cc[i, j] = N;
                    color[N] = (int)(map[i][j] - '0');
                    adj[N, N] = true;
                    dfs(i, j);
                }
            }
        }

        Console.WriteLine(Play(false));
        Console.WriteLine(Play(true));
    }

    #region UTIL
    class Scanner {
        System.IO.TextReader reader;
        char[] sep = new char[] { ' ', '\t', '\n', '\r' };
        string[] tok = new string[] { };
        int tokp = 0;

        bool update() {
            while (tokp >= tok.Length) {
                string line = reader.ReadLine();
                if (line == null)
                    return false;
                tok = line.Split(sep, StringSplitOptions.RemoveEmptyEntries);
                tokp = 0;
            }
            return true;
        }

        public Scanner(System.IO.TextReader reader) { this.reader = reader; }
        public bool HasNext() { return update(); }
        public string Next() { return update() ? tok[tokp++] : null; }
        public int NextInt() { return int.Parse(Next()); }
        public double NextDouble() { return double.Parse(Next()); }
    }

    public static void Main(string[] args) {
        System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
        new Program().Run();
    }
#endregion
}
