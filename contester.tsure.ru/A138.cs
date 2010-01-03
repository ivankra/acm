using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    struct Roach : IComparable<Roach> {
        public int x, y, index;

        public int CompareTo(Roach r) {
            if (y != r.y) return r.y - y;
            return index - r.index;
        }
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();

        Roach[] v = new Roach[N];
        for (int i = 0; i < N; i++) {
            v[i].x = input.NextInt();
            v[i].y = input.NextInt();
            v[i].index = i;
        }

        Array.Sort(v);

        for (int i = 0; i < N; i++)
            Console.WriteLine("{0} {1}", v[i].x, v[i].y);
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
