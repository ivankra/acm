using System;
using System.Collections.Generic;

public class Program
{
    bool possible(int A, int B, int K)
    {
        if (K <= 1) return true;
        if (K == 2) return (2 * A + 2 * B - 4) % 2 == 0;

        if (A % K == 1 && B % K == 1) return true;
        if (A % K == 0 && B % K == 2) return true;
        if (A % K == 2 && B % K == 0) return true;

        return false;
    }

    void Run()
    {
        Scanner input = new Scanner(Console.In);

        int X = input.NextInt();
        int Y = input.NextInt();

        int N = input.NextInt();
        for (int i = 0; i < N; i++)
        {
            int A = input.NextInt();
            Console.WriteLine(possible(X, Y, A) ? "yes" : "no");
        }
    }

    class Scanner
    {
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
