using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    int[] a;
    void mul(int k) {
        int carry = 0;
        for (int i = 0; i < a.Length; i++) {
            carry += k * a[i];
            a[i] = carry % 10;
            carry /= 10;
        }
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        if (N <= 0) {
            Console.WriteLine("0");
            return;
        }

        a = new int[1000];
        a[0] = 1;
        while (N > 4) { mul(3); N -= 3; }
        mul(N);

        int i;
        for (i = a.Length - 1; a[i] == 0; i--) ;

        StringBuilder sb = new StringBuilder();
        while (i >= 0) sb.Append(a[i--]);
        Console.WriteLine(sb.ToString());
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
