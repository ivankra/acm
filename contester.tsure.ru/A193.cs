using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        int K = input.NextInt();
        const int MOD = 1000000007;

        int[] f = new int[K + 1];
        f[0] = 1;

        for (int n = 1; n <= N; ++n) {
            for (int k = 1; k <= K; k++)
                f[k] = (f[k - 1] + f[k]) % MOD;

            for (int k = K; k >= 1; --k)
                f[k] = ((f[k] - (k - n >= 0 ? f[k - n] : 0)) % MOD + MOD) % MOD;
            f[0] = 1;
        }

        Console.WriteLine(f[K]);
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
