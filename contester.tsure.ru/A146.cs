using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        int[] a = new int[N+1];
        int[] s = new int[N + 1];
        for (int i = 1; i <= N; i++) {
            a[i] = input.NextInt();
            s[i] = s[i - 1] + a[i];
        }

        for (int cut = N / 2; cut <= N; cut++) {
            if (s[cut] - s[cut - N / 2] == N / 4) {
                if (cut == N / 2)
                    Console.WriteLine("1 {0} {1}", cut, cut + 1);
                else
                    Console.WriteLine("2 {0} {1} {2} {3}", cut - N / 2, cut - N / 2 + 1, cut, cut + 1);
                return;
            }
        }

        throw new Exception("*** error ***");
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
