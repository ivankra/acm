using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        int[] ten = new int[11];
        for (int i = 0; i <= 10; i++)
            ten[i] = (i == 0 ? 1 : ten[i-1]*10);

        int N = input.NextInt();
        int[] a = new int[16];
        int current = 1;

        while (true) {
            int n = 0;
            for (int t = current; t != 0; t /= 10)
                a[n++] = t % 10;

            for (int i = n - 1; i >= 0; --i) {
                for (int j = i + 1; j < n; ++j) {
                    if (a[i] == a[j]) {
                        current += ten[i];
                        goto next;
                    }
                }
            }

            if (--N == 0) break;
            current++;

        next: ;

        }

        Console.WriteLine(current);
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
