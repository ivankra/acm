using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

public class Program
{
    int N, M, res;
    int[] color;
    bool[,] adj;

    bool dfs(int x, int c)
    {
        if (color[x] != 0)
            return color[x] == c;

        color[x] = c;
        res++;

        for (int y = 0; y < N; y++)
            if (adj[x, y] && !dfs(y, c == 1 ? 2 : 1)) return false;
        return true;
    }

    void Run()
    {
        Scanner input = new Scanner(Console.In);

        N = input.NextInt();
        M = input.NextInt();
        adj = new bool[N, N];

        for (int i = 0; i < M; i++)
        {
            int x = input.NextInt() - 1;
            int y = input.NextInt() - 1;
            if (x < 0 || x >= N || y < 0 || y >= N || x == y) continue;
            adj[x, y] = adj[y, x] = true;
        }

        color = new int[N];
        res = 0;

        if (!dfs(0, 1))
            Console.WriteLine("0");
        else
            Console.WriteLine(res);
    }

    class Scanner
    {
        TextReader reader;
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

        public Scanner(TextReader reader) { this.reader = reader; }
        public bool HasNext() { return update(); }
        public string Next() { return update() ? tok[tokp++] : null; }
        public int NextInt() { return int.Parse(Next()); }
        public double NextDouble() { return double.Parse(Next()); }
    }

    public static void Main(string[] args) {
        System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
        new Program().Run();
    }
}
