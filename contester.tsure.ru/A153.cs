using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    bool[,] label;

    int Solve() {
        int[,] dist = new int[101, 101];

        Queue<int> Q = new Queue<int>();
        Q.Enqueue(100);
        Q.Enqueue(0);
        Q.Enqueue(0);

        int[] s = new int[3];
        int[] t = new int[3];

        while (Q.Count != 0) {
            for (int i = 0; i < 3; i++)
                s[i] = Q.Dequeue();

            int d = dist[s[0], s[1]];
            if (s[2] == 1)
                return d;

            for (int a = 0; a < 3; a++) {
                for (int b = 0; b < 3; b++) {
                    if (a == b) continue;

                    for (int j = 0; j < 3; j++)
                        t[j] = s[j];

                    while (t[a] > 0 && t[b] < 100) {
                        t[a]--; t[b]++;
                        if (label[a, t[a]] || label[b, t[b]]) {
                            if (dist[t[0], t[1]] == 0) {
                                dist[t[0], t[1]] = d + 1;
                                for (int k = 0; k < 3; k++)
                                    Q.Enqueue(t[k]);
                            }
                        }
                    }
                }
            }
        }

        return -1;
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        label = new bool[3, 101];
        for (int i = 1; i <= N; i++) {
            int n = input.NextInt();
            label[0, n] = label[1, n] = true;
        }

        for (int i = 0; i < 3; i++)
            label[i, 0] = label[i, 100] = true;

        int res = Solve();
        if (res <= 0)
            Console.WriteLine("NO");
        else
            Console.WriteLine("YES\n{0}", res);
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
