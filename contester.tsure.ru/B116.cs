using System;
using System.Collections.Generic;
using System.Text;

public class Program {

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        char ch = input.Next()[0];

        for (int i = 1;; i++) {
            Console.WriteLine(new string(ch, 2 * N + 1));
            if (i == 3) break;

            for (int j = 0; j < N-1; j++) {
                int k = (i == 1 ? 2 * j + 1 : 2 * (N-2-j) + 1);
                string s = new string('.', (2*N-1-k)/2);
                string t = new string(ch, k);
                Console.WriteLine(ch + s + t + s + ch);
            }
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
    }

    public static void Main(string[] args) {
        System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
        new Program().Run();
    }
}
