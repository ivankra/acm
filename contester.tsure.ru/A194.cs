using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();

        int[,] a = new int[N, N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i, j] = input.NextInt();

        int[] dp = new int[1 << N];
        dp[0] = 0;
        for (int mask = 1; mask < (1 << N); ++mask) {
            int i = -1;
            for (int j = 0; j < N; j++)
                i += (mask >> j) & 1;

            dp[mask] = int.MaxValue;
            for (int j = 0; j < N; j++)
                if ((mask & (1 << j)) != 0) {
                    int t = a[i, j] + dp[mask ^ (1 << j)];
                    if (t < dp[mask]) dp[mask] = t;
                }
        }

        Console.WriteLine(dp[(1 << N) - 1]);
    }

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
    }

    public static void Main(string[] args) {
        System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
        new Program().Run();
    }
}
