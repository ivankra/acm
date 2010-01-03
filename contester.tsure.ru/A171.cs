using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    int N, ans;
    int[] kid, sib;

    void dfs(int x, int p, int dist) {
        if (dist > ans) ans = dist;

        for (int y = kid[x]; y != 0; y = sib[y])
            if (y != p) dfs(y, x, dist + 1);
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        N = input.NextInt();
        kid = new int[N + 10];
        sib = new int[N + 10];

        for (int x = 1; x <= N; x++) {
            int y;
            while ((y = input.NextInt()) != 0) {
                sib[y] = kid[x];
                kid[x] = y;
            }
        }

        ans = 0;
        dfs(1, -1, 0);
        Console.WriteLine(ans);
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
