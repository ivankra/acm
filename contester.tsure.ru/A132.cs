using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    class Bignum : IComparable<Bignum> {
        const int LEN = 505;
        byte[] a;

        public Bignum(int x) {
            a = new byte[LEN];
            a[0] = (byte)x;
        }

        public Bignum(string s) {
            a = new byte[LEN];
            for (int i = 0; i < s.Length; i++)
                a[s.Length - 1 - i] = (byte)(s[i] - '0');
        }

        public Bignum(Bignum b) {
            a = new byte[LEN];
            for (int i = 0; i < LEN; i++)
                a[i] = b.a[i];
        }

        public void Add(Bignum y) {
            int carry = 0;
            for (int i = 0; i < LEN; i++) {
                carry += a[i] + y.a[i];
                a[i] = (byte)(carry % 10);
                carry /= 10;
            }
        }

        public int CompareTo(Bignum y) {
            for (int i = LEN - 1; i >= 0; i--)
                if (a[i] != y.a[i]) return a[i] > y.a[i] ? 1 : -1;
            return 0;
        }

        public override string ToString() {
            StringBuilder res = new StringBuilder();
            int i;
            for (i = LEN - 1; i > 0 && a[i] == 0; i--);
            while (i >= 0)
                res.Append((char)(a[i--] + '0'));
            return res.ToString();
        }
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();

        Bignum[] v = new Bignum[N];
        for (int i = 0; i < N; i++) {
            v[i] = new Bignum(input.Next());
        }
        Array.Sort(v);

        for (int i = 0; i <= N-3; i++) {
            Bignum t = new Bignum(v[i]);
            t.Add(v[i+1]);
            if (t.CompareTo(v[i+2]) > 0) {
                Console.WriteLine("{0} {1} {2}", v[i], v[i+1], v[i+2]);
                return;
            }
        }

        Console.WriteLine("0 0 0");
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
