using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void put(char[,] buf, int x, char ch, char border) {
        buf[2, x] = ch;
        buf[0, x] = border;
        buf[1, x - 1] = buf[1, x + 1] = border;
        buf[2, x - 2] = buf[2, x + 2] = border;
        buf[3, x - 1] = buf[3, x + 1] = border;
        buf[4, x] = border;
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        string s = input.Next();
        int N = s.Length;

        char[,] buf = new char[5, 4 * N + 1];
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 4 * N + 1; j++)
                buf[i, j] = '.';

        for (int i = 0; i < N; i++)
            put(buf, 4 * i + 2, s[i], '#');

        for (int i = 2; i < N; i += 3)
            put(buf, 4 * i + 2, s[i], '*');

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 4 * N + 1; j++)
                Console.Write(buf[i, j]);
            Console.WriteLine();
        }
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
        public double NextDouble() { return double.Parse(Next()); }
    }

    public static void Main(string[] args) {
        System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
        new Program().Run();
    }
}
