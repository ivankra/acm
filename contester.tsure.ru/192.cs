using System;
using System.Collections.Generic;

public class Program
{
    int[,] mat;
    int N;
 
    void Run()
    {
        Scanner input = new Scanner(Console.In);

        N = input.NextInt();
        mat = new int[N, N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                mat[i, j] = input.NextInt();

        int res = 0;
        for (int y1 = 0; y1 < N; y1++) {
            for (int x1 = 0; x1 < N; x1++) {
                int c = mat[y1, x1];
                for (int y2 = y1; y2 < N; y2++) {
                    for (int x2 = (y1 == y2 ? x1 + 1 : 0); x2 < N; x2++) {
                        if (mat[y2, x2] != c) continue;

                        int y3 = y2 + (x2 - x1);
                        int x3 = x2 + (y1 - y2);
                        if (y3 < 0 || y3 >= N || x3 < 0 || x3 >= N || mat[y3, x3] != c) continue;

                        int y4 = y1 + (x2 - x1);
                        int x4 = x1 + (y1 - y2);
                        if (y4 < 0 || y4 >= N || x4 < 0 || x4 >= N || mat[y4, x4] != c) continue;

                        res++;
                    }
                }
            }
        }

        Console.WriteLine(res/2);
    }

    class Scanner
    {
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
}
