using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    struct Point : IComparable<Point> {
        public int x, y;

        public int CompareTo(Point p) {
            if (x != p.x) return x > p.x ? 1 : -1;
            if (y != p.y) return y > p.y ? 1 : -1;
            return 0;
        }

        public override string ToString() {
            return string.Format("{0} {1}", x, y);
        }
    }

    int cross(Point o, Point a, Point b) {
        long t = (a.x - o.x) * (long)(b.y - o.y) - (a.y - o.y) * (long)(b.x - o.x);
        if (t == 0) return 0;
        return t > 0 ? 1 : -1;
    }

    int N;
    Point[] P;

    int[] Q, mark;

    void eraseHull() {
        for (int i = 0; i < N; i++)
            mark[i] = 0;

        for (int pass = 0; pass < 2; pass++) {
            int m = 0;
            for (int i = 0; i < N; ++i) {
                int j = (pass == 1 ? N - 1 - i : i);
                while (m >= 2 && cross(P[Q[m - 2]], P[Q[m - 1]], P[j]) <= 0) m--;
                Q[m++] = j;
            }

            for (int i = 1; i < m; ++i) {
                int a = Q[i - 1], b = Q[i];
                if (a > b) { int t = a; a = b; b = t; }

                mark[a] = mark[b] = 1;
                for (int j = a + 1; j < b; ++j)
                    if (cross(P[a], P[j], P[b]) == 0) mark[j] = 1;
            }
        }

        int n = 0;
        for (int i = 0; i < N; i++) {
            if (mark[i] == 0) {
                if (n != i) P[n] = P[i];
                n++;
            }
        }
        N = n;
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        N = input.NextInt();

        P = new Point[N];
        for (int i = 0; i < N; i++) {
            P[i].x = input.NextInt();
            P[i].y = input.NextInt();
        }

        Array.Sort<Point>(P);

        Q = new int[N + N];
        mark = new int[N];

        int res = 0;
        while (N > 3) {
            eraseHull();
            res++;
        }

        if (N != 1) throw new Exception("N != 1");

        Console.WriteLine(res);
        Console.WriteLine(P[0]);
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
