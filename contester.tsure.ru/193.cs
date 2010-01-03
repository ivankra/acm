using System;
using System.Collections.Generic;

public class Program
{
    struct Point {
        public int x, y;

        public int CompareTo(Point p) {
            if (x != p.x) return x < p.x ? -1 : 1;
            if (y != p.y) return y < p.y ? -1 : 1;
            return 0;
        }

        public override string ToString() {
            return string.Format("({0}, {1})", x, y);
        }
    }

    int cross(Point o, Point a, Point b) {
        int t = (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
        if (t == 0) return 0;
        return t < 0 ? -1 : 1;
    }

    bool onSeg(Point p, Point a, Point b) {
        if (cross(p, a, b) != 0) return false;
        if (p.x < a.x && p.x < b.x) return false;
        if (p.x > a.x && p.x > b.x) return false;
        if (p.y < a.y && p.y < b.y) return false;
        if (p.y > a.y && p.y > b.y) return false;
        return true;
    }

    bool mergeSegments(ref Point a, ref Point b, Point c, Point d) {
        if (cross(a, b, c) != 0 || cross(a, b, d) != 0) return false;

        if (!onSeg(c, a, b) && !onSeg(d, a, b) && !onSeg(a, c, d) && !onSeg(b, c, d))
            return false;

        Point A = a, B = a;
        foreach (Point p in new Point[] { a, b, c, d }) {
            if (p.CompareTo(A) < 0) A = p;
            if (p.CompareTo(B) > 0) B = p;
        }

        a = A;
        b = B;
        return true;
    }

    bool segCross(Point a, Point b, Point c, Point d) {
        if (cross(a, b, c) == 0 && cross(a, b, d) == 0) return false;

        int u = cross(c, a, b) * cross(d, a, b);
        int v = cross(a, c, d) * cross(b, c, d);
        if (u <= 0 && v <= 0) return true;

        return false;
    }

    void isec(out double x, out double y, Point A, Point B, Point C, Point D) {
        double a1 = A.y - B.y, b1 = B.x - A.x, c1 = a1 * A.x + b1 * A.y;
        double a2 = C.y - D.y, b2 = D.x - C.x, c2 = a2 * C.x + b2 * C.y;
        double det = a1 * b2 - a2 * b1;
        x = (c1 * b2 - c2 * b1) / det;
        y = (a1 * c2 - a2 * c1) / det;
    }

    bool coincident(Point A, Point B, Point C, Point D, Point E, Point F) {
        double[] x = new double[3];
        double[] y = new double[3];

        isec(out x[0], out y[0], A, B, C, D);
        isec(out x[1], out y[1], A, B, E, F);
        isec(out x[2], out y[2], E, F, C, D);

        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                double d = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
                if (d > 0.0001) return false;
            }
        }

        return true;
    }

    void Run()
    {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        Point[,] r = new Point[N, 2];

        for (int i = 0; i < N; i++) {
            r[i, 0].x = input.NextInt();
            r[i, 0].y = input.NextInt();
            r[i, 1].x = input.NextInt();
            r[i, 1].y = input.NextInt();
            if (r[i, 0].CompareTo(r[i, 1]) == 0) {
                i--;
                N--;
            }
        }

        while (true) {
            bool changed = false;

            for (int i = 0; i < N; i++) {
                for (int j = i + 1; j < N; j++) {
                    if (mergeSegments(ref r[i, 0], ref r[i, 1], r[j, 0], r[j, 1])) {
                        for (int k = j + 1; k < N; k++) {
                            r[k - 1, 0] = r[k, 0];
                            r[k - 1, 1] = r[k, 1];
                        }
                        N--;
                        changed = true;
                        break;
                    }
                }
            }

            if (!changed) break;
        }

        //for (int i = 0; i < N; i++)
        //    Console.WriteLine("Segment {0}: {1} -- {2}", i+1, r[i, 0], r[i, 1]);

        int res = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (!segCross(r[i, 0], r[i, 1], r[j, 0], r[j, 1])) continue;
                for (int k = j + 1; k < N; k++) {
                    if (!segCross(r[i, 0], r[i, 1], r[k, 0], r[k, 1])) continue;
                    if (!segCross(r[j, 0], r[j, 1], r[k, 0], r[k, 1])) continue;

                    if (coincident(r[i, 0], r[i, 1], r[j, 0], r[j, 1], r[k, 0], r[k, 1]))
                        continue;

                    res++;
                }
            }
        }

        Console.WriteLine(res);
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
