using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        LinkedList<int>[] v = new LinkedList<int>[3];
        for (int k = 1; k <= 2; k++) {
            int x;
            v[k] = new LinkedList<int>();
            while ((x = input.NextInt()) != 0)
                v[k].AddLast(x);
        }

        string s;
        int buffer = 0;

        while ((s = input.Next()) != "0") {
            int k = input.NextInt();
            switch (s) {
                case "PopL":
                    buffer = v[k].First.Value;
                    v[k].RemoveFirst();
                    break;
                case "PopR":
                    buffer = v[k].Last.Value;
                    v[k].RemoveLast();
                    break;
                case "PushL":
                    v[k].AddFirst(buffer);
                    break;
                case "PushR":
                    v[k].AddLast(buffer);
                    break;
            }
        }

        for (int k = 1; k <= 2; k++) {
            foreach (int x in v[k])
                Console.Write("{0} ", x);
            Console.WriteLine("0");
        }
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
