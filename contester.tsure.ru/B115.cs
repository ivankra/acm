using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();

        int[,] a = new int[N, N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i, j] = input.NextInt();

        List<int> v = new List<int>();
        for (int i = 0; i < N; i++) {
            int s = 0, t = 0;
            for (int j = 0; j < N; j++) {
                s += a[i, j];
                t += a[j, i];
            }
            v.Add(s);
            v.Add(t);
        }

        {
            int s = 0, t = 0;
            for (int i = 0; i < N; i++) {
                s += a[i, i];
                t += a[i, N - 1 - i];
            }
            v.Add(s);
            v.Add(t);
        }

        v.Sort();
        if (v[0] == v[v.Count - 1])
            Console.WriteLine("YES");
        else
            Console.WriteLine("NO");
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
