using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    double f(int N, double L, double K) {
        double res = 0;
        double t = L;
        for (int i = 0; i < N; i++) {
            res += t * (i == 0 ? 6 : 5);
            t = t * (i == 0 ? 6 : 5) / K;
        }
        return res;
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        double L = input.NextDouble();
        double K = input.NextDouble();

        Console.WriteLine("{0:0.00000}", f(N, L, K));
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
