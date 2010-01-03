using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    int N;

    void rec(int ap, int aq, int bp, int bq) {
        int p = ap + bp;
        int q = aq + bq;
        if (q > N) return;

        rec(ap, aq, p, q);
        Console.WriteLine("{0}/{1}", p, q);
        rec(p, q, bp, bq);
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        N = input.NextInt();
        rec(0, 1, 1, 1);
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
