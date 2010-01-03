using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    bool Check(string s) {
        char[] stack = new char[s.Length + 10];
        int k = 0;

        foreach (char c in s) {
            if (c == '(') {
                stack[k++] = ')';
            } else if (c == '[') {
                stack[k++] = ']';
            } else if (c == '{') {
                stack[k++] = '}';
            } else {
                if (k == 0 || stack[k-1] != c) return false;
                k--;
            }
        }

        return k == 0;
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        string s = input.Next();

        Console.WriteLine(Check(s) ? "Yes" : "No");
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
