using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

public class Program
{
    int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

    int solve(int n, int m)
    {
        if (n <= 0 || m <= 0) return 0;

        int g = gcd(n, m);
        if (g != 1) return solve(n/g, m/g) * g;

        if (n < m) return solve(m, n);

        int res = 0;
        for (int x = 0; x < m; x++)
        {
            int y1 = n * x / m;
            int y2 = (n * (x + 1) + m - 1) / m;
            res += y2 - y1;
        }
        return res;
    }

    void Run()
    {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt() - 1;
        int M = input.NextInt() - 1;
        Console.WriteLine(solve(N, M));
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
