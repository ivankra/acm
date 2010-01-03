using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    int N, M;
    char[][] map;

    void dfs(int i, int j) {
        if (i < 0 || i >= N || j < 0 || j >= M || map[i][j] == '.') return;
        map[i][j] = '.';
        dfs(i - 1, j);
        dfs(i + 1, j);
        dfs(i, j - 1);
        dfs(i, j + 1);
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        N = input.NextInt();
        M = input.NextInt();
        map = new char[N][];
        for (int i = 0; i < N; i++)
            map[i] = input.Next().ToCharArray();

        int res = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (map[i][j] == '#') {
                    res++;
                    dfs(i, j);
                }
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
