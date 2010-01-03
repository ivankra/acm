using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        int A = input.NextInt();
        int B = input.NextInt();
        int D = input.NextInt();

        bool[] sieve = new bool[B + 10];
        sieve[0] = sieve[1] = true;
        for (int i = 2; i * i <= B; ++i) {
            if (!sieve[i]) {
                for (int j = i * i; j <= B; j += i)
                    sieve[j] = true;
            }
        }

        int res = 0;
        for (int i = A; i <= B; ++i) {
            if (!sieve[i]) {
                int t = i;
                while (t > 0) {
                    if (t % 10 == D) { res++; break; }
                    t /= 10;
                }
            }
        }

        Console.WriteLine(res);
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
