using System;
using System.Text;

public class Program {
    class Bignum {
        const int RADIX = 1000000000;
        int[] a;
        int n;

        public Bignum(int x) {
            a = new int[20000];
            a[0] = x;
            n = 1;
        }

        public void Add(Bignum y) {
            int carry = 0;
            if (n < y.n) n = y.n;
            for (int i = 0; i < n; ++i) {
                carry += a[i];
                if (i < y.n) {
                    carry += y.a[i];
                } else if (carry == 0) {
                    break;
                }
                a[i] = carry % RADIX;
                carry /= RADIX;
            }

            if (carry != 0)
                a[n++] = carry;
        }

        public override string ToString() {
            StringBuilder res = new StringBuilder();
            res.AppendFormat("{0}", a[n-1]);
            for (int i = n-2; i >= 0; i--)
                res.AppendFormat("{0:000000000}", a[i]);
            return res.ToString();
        }
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        long A = input.NextInt();
        long B = input.NextInt();
        int N = input.NextInt();

        Bignum a = new Bignum(0);
        Bignum b = new Bignum(0);
        Bignum one = new Bignum(1);

        int last = 0;
        for (int i = 0; i < N; i++) {
            while (A % 2 == 0 && B % 2 == 0) { A /= 2; B /= 2; }

            if (A > B || (A == B && last == 0)) {
                B *= 2;
                last = 0;
                a.Add(a);
                a.Add(one);
            } else {
                A *= 2;
                last = 1;
                b.Add(b);
                b.Add(one);
            }
        }

        a.Add(b);
        Console.WriteLine(a);
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
