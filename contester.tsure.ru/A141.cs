using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    int solve(int[] a) {
        Array.Sort(a);

        int res = 0;
        int i;
        for (i = a.Length - 1; i >= 2;) {
            if (a[0] + a[i - 1] <= 2 * a[1]) {
                res += a[0] + a[i];
                i--;
            } else {
                res += a[0] + a[1] + a[i] + a[1];
                i -= 2;
            }
        }

        res += a[i];

        return res;
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        int[] a = new int[N];
        for (int i = 0; i < N; i++)
            a[i] = input.NextInt();

        Console.WriteLine(solve(a));
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
