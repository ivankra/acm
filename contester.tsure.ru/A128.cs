using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        N *= N;

        const int LEN = 1024;
        const int RADIX = 1000000000;

        int[] a = new int[LEN];
        int[] b = new int[LEN];
        a[0] = 1;

        for (int r = 16; r >= 0; r--) {
            for (int i = 0; i < LEN; i++) { b[i] = a[i]; a[i] = 0; }
            for (int i = 0; i < LEN; i++) {
                long carry = 0;
                if (b[i] == 0) continue;
                for (int j = 0, k = i; k < LEN; j++, k++) {
                    carry += a[k] + b[i] * (long)b[j];
                    a[k] = (int)(carry % RADIX);
                    carry /= RADIX;
                }
            }

            if ((N & (1 << r)) != 0) {
                int carry = 0;
                for (int i = 0; i < LEN; i++) {
                    carry += 2 * a[i];
                    a[i] = carry % RADIX;
                    carry /= RADIX;
                }
            }
        }

        a[0]--;

        StringBuilder res = new StringBuilder();
        int p = LEN - 1;
        while (a[p] == 0) p--;

        res.AppendFormat("{0}", a[p]);
        for (p--; p >= 0; p--)
            res.AppendFormat("{0:000000000}", a[p]);

        Console.WriteLine(res.ToString());
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
