using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();

        int best = int.MaxValue;
        for (int pass = 0; pass < 2; pass++) {
            for (int n2 = 0; n2 < 12; n2++) {
                for (int n3 = 0; n3 < 12; n3++) {
                    int n1 = (N - n2 * 12 - n3 + 143) / 144;
                    if (n1 < 0) n1 = 0;

                    int cost = n1 * 11400 + n2 * 1025 + n3 * 105;
                    if (cost > best) continue;

                    if (pass == 0)
                        best = cost;
                    else {
                        Console.WriteLine("{0} {1} {2}", n1, n2, n3);
                        return;
                    }
                }
            }
        }
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
