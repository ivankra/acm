using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    int N, R;
    char[,] map, mm;
    char[] next;
    int[] dx, dy;

    void dfs(int y, int x) {
        R++;

        char ch = next[mm[y, x]];
        mm[y, x] = ch;

        for (int sign = -1; sign <= 1; sign += 2) {
            int y1 = y + sign * dy[ch];
            int x1 = x + sign * dx[ch];
            if (mm[y1, x1] == ch) {
                dfs(y1, x1);
            }
        }
    }

    int bestAt(int y0, int x0) {
        R = 0;
        for (int i = 0; i <= N+1; i++)
            for (int j = 0; j <= N+1; j++)
                mm[i, j] = map[i, j];
        dfs(y0, x0);
        return R;
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        N = input.NextInt();
        map = new char[N + 2, N + 2];
        mm = new char[N + 2, N + 2];

        for (int i = 0; i < N + 2; i++)
            for (int j = 0; j < N + 2; j++)
                map[i, j] = '#';

        for (int i = 1; i <= N; i++) {
            string s = input.Next();
            for (int j = 1; j <= N; j++)
                map[i, j] = s[j-1];
        }

        next = new char[256];
        dx = new int[256];
        dy = new int[256];
        for (int i = 0; i < 4; i++) {
            next["|/-\\"[i]] = "/-\\|"[i];
            dy["|/-\\"[i]] = "2212"[i] - '1';
            dx["|/-\\"[i]] = "1022"[i] - '1';
        }

        int best = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                best = Math.Max(best, bestAt(i, j));
            }
        }
        Console.WriteLine(best);
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
