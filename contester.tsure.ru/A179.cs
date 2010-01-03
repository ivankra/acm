using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    string Reverse(string s) {
        char[] a = s.ToCharArray();
        Array.Reverse(a);
        return new string(a);
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        string a = input.Next().Trim('0');
        string b = input.Next().Trim('0');

        string c = "";
        int carry = 0;
        for (int i = 0; i < a.Length || i < b.Length || carry != 0; i++) {
            if (i < a.Length) carry += a[i] - '0';
            if (i < b.Length) carry += b[i] - '0';
            c += (char)('0' + (carry % 10));
            carry /= 10;
        }
        c = c.Trim('0');

        Console.WriteLine(c);
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
