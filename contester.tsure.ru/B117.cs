using System;
using System.Collections.Generic;
using System.Text;

public class Program {

    void Run() {
        Scanner input = new Scanner(Console.In);

        string[] a = new string[3];
        for (int i = 0; i < 3; i++)
            a[i] = input.Next();

        int max = 0, min = 0, max_c = 1;
        for (int i = 1; i < 3; i++) {
            if (a[i].Length > a[max].Length ||
                (a[i].Length == a[max].Length && a[i].CompareTo(a[max]) > 0)) {
                max = i;
                max_c = 1;
            } else if (a[i] == a[max]) {
                max_c++;
            } else {
                min = i;
            }
        }

        string[] names = new string[] { "Mary", "Klaus", "Peter" };

        if (max_c == 1)
            Console.WriteLine(names[max]);
        else if (max_c == 2)
            Console.WriteLine(names[min]);
        else
            Console.WriteLine("Draw");
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
