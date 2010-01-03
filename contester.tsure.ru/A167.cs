using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    int N;
    int[] kid, sib, parent, value;
    int[,] memo;
    bool[,] got;

    int vertCov(int x, int flag) {
        if (got[x, flag])
            return memo[x, flag];

        int with = value[x];
        for (int y = kid[x]; y != 0; y = sib[y])
            with += vertCov(y, 1);

        int without = 0;
        for (int y = kid[x]; y != 0; y = sib[y])
            without += vertCov(y, 0);

        got[x, flag] = true;
        return memo[x, flag] = (flag == 0 ? Math.Max(with, without) : without);
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        N = input.NextInt();

        value = new int[N + 1];
        for (int i = 1; i <= N; i++)
            value[i] = input.NextInt();

        kid = new int[N + 1];
        sib = new int[N + 1];
        parent = new int[N + 1];

        for (int i = 1; i < N; i++) {
            int x = input.NextInt();
            int p = input.NextInt();
            sib[x] = kid[p];
            kid[p] = x;
            parent[x] = p;
        }

        int root = 0;
        for (int i = 1; i <= N; i++)
            if (parent[i] == 0) root = i;

        memo = new int[N + 1, 2];
        got = new bool[N + 1, 2];

        int res = Math.Max(vertCov(root, 0), vertCov(root, 1));
        Console.WriteLine(res);
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
