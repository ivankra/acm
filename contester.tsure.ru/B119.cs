using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    struct Time : IComparable<Time> {
        public int a, b, c;

        public int CompareTo(Time t) {
            if (a != t.a) return a - t.a;
            if (b != t.b) return b - t.b;
            return c - t.c;
        }
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();

        Time[] v = new Time[N];
        for (int i = 0; i < N; i++) {
            v[i].a = input.NextInt();
            v[i].b = input.NextInt();
            v[i].c = input.NextInt();
        }

        Array.Sort(v);

        foreach (Time t in v)
            Console.WriteLine("{0} {1} {2}", t.a, t.b, t.c);
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
