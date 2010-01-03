using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        string s = input.Next();
        int N = s.Length;

        int[, ,] dp = new int[N, N, 3];
        for (int len = 1; len <= N; len++) {
            for (int a = 0; a <= N-len; a++) {
                int b = a + len - 1;
                for (int side = 0; side < 3; side++) {
                    int res = b - a + 1;
                    for (int c = a; c <= b; c++) {
                        int cost = 1;
                        if (side == 1 && a > 0 && s[a - 1] == s[c]) cost = 0;
                        if (side == 2 && b + 1 < N && s[b + 1] == s[c]) cost = 0;

                        if (a < c) cost += dp[a, c - 1, 2];
                        if (c < b) cost += dp[c + 1, b, 1];

                        if (cost < res)
                            res = cost;
                    }
                    dp[a, b, side] = res;
                }
            }
        }

        Console.WriteLine(dp[0, N - 1, 0]);
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
        public double NextDouble() { return double.Parse(Next()); }
    }

    public static void Main(string[] args) {
        System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
        new Program().Run();
    }
}
