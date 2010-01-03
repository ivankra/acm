using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    int[] cost;
    int N;

    void recover(int n) {
        if (n >= N) return;

        int c = cost[n];
        for (int y = 1; y <= 9; y++)
            if (n + y <= N && 1 + cost[n + y] == c) {
                Console.WriteLine("ADD A {0}", y);
                recover(n + y);
                return;
            }

        for (int y = 2; y <= 9; y++)
            if (n * y <= N && 1 + cost[n * y] == c) {
                Console.WriteLine("MUL A {0}", y);
                recover(n * y);
                return;
            }

        if (n >= 2 && n < 1010 && n * n <= N && 1 + cost[n * n] == c) {
            Console.WriteLine("MUL A A");
            recover(n * n);
            return;
        }
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        N = input.NextInt();
        if (N == 0) {
            Console.Write("1\nMUL A 0\n");
            return;
        }

        cost = new int[N + 1];
        cost[N] = 0;

        for (int n = N - 1; n >= 1; n--) {
            cost[n] = int.MaxValue / 2;

            for (int y = 1; y <= 9; y++)
                if (n + y <= N && 1 + cost[n + y] < cost[n])
                    cost[n] = 1 + cost[n + y];

            for (int y = 2; y <= 9; y++)
                if (n * y <= N && 1 + cost[n * y] < cost[n])
                    cost[n] = 1 + cost[n * y];

            if (n >= 2 && n < 1010 && n*n <= N && 1 + cost[n*n] < cost[n])
                cost[n] = 1 + cost[n*n];
        }

        int bestCost = int.MaxValue;
        int bestA = 0;
        string bestS = "";

        for (int x = 0; x <= 9; x++) {
            for (int y = 0; y <= 9; y++) {
                if (x + y > 0 && x + y <= N && cost[x + y] < bestCost) {
                    bestCost = cost[x + y];
                    bestA = x + y;
                    bestS = string.Format("ADD {0} {1}", x, y);
                }

                if (x * y > 0 && x * y <= N && cost[x * y] < bestCost) {
                    bestCost = cost[x * y];
                    bestA = x * y;
                    bestS = string.Format("MUL {0} {1}", x, y);
                }
            }
        }

        Console.WriteLine(bestCost + 1);
        Console.WriteLine(bestS);
        recover(bestA);
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
