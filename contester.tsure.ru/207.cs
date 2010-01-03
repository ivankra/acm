using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        //Scanner input = new Scanner(Console.In);

        string s = Console.ReadLine();
        int x = 1;

        foreach (char c in s) {
            int a, b;
            if (c == 'A') { a = 1; b = 2; }
            else if (c == 'B') { a = 2; b = 3; }
            else if (c == 'C') { a = 1; b = 3; }
            else continue;

            if (x == a) x = b;
            else if (x == b) x = a;
        }

        Console.WriteLine(x);
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
