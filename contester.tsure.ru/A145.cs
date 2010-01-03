using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    bool fits(int a, int b, int A, int B) {
        if (a > b) { int t = a; a = b; b = t; }
        if (A < B) { int t = A; A = B; B = t; }

        double left = 0, right = 1;
        for (int k = 0; k < 50; k++) {
            double t = (left + right) / 2;
            double s = Math.Sqrt(1 - t * t);

            double W = a * t + b * s;
            double H = a * s + b * t;
            const double EPS = 1e-9;

            if (W < A + EPS && H < B + EPS)
                return true;

            if (H < B)
                left = t;
            else
                right = t;
        }

        return false;
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        string res = "";

        for (int i = 0; i < N; i++) {
            int a = input.NextInt();
            int b = input.NextInt();
            int A = input.NextInt();
            int B = input.NextInt();
            res += fits(a, b, A, B) ? "1" : "0";
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
