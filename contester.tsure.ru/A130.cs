using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    long f(long n) { return n <= 9 ? n : (n % 10 + f(n / 10)); }

    void Run() {
        Scanner input = new Scanner(Console.In);

//  abcd+abc+ab+a = abc(d+1)+ab+a = ab(c(d+1)+1) + a = a(b(c(d+1)+1)+1)

        int T = input.NextInt();
        for (int cs = 1; cs <= T; cs++) {
            int N = input.NextInt();
            int[] A = new int[N];

            for (int i = 0; i < N; i++)
                A[i] = input.NextInt();

            int L = N + N, RADIX = 1000000000;
            long[] big = new long[L];

            for (int t = N-1; t >= 0; t--) {
                long carry = 0;
                big[0]++;
                for (int i = 0; i < L; i++) {
                    carry += A[t] * big[i];
                    big[i] = carry % RADIX;
                    carry /= RADIX;
                }
            }

            long res = 0;
            for (int i = 0; i < L; i++)
                res += big[i];

            while (res >= 10)
                res = f(res);

            Console.WriteLine(res);
        }
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
