using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    struct Rect : IComparable<Rect> {
        public int a, b;

        public int CompareTo(Rect r) {
            return a * b - r.a * r.b;
        }

        public override string ToString() {
            return string.Format("{0}x{1}", a, b);
        }

        public bool FitsOnto(Rect r) {
            for (int pass = 0; pass < 4; pass++) {
                int A = (pass & 1) == 0 ? a : b;
                int B = (pass & 1) == 0 ? b : a;

                int C = (pass & 2) == 0 ? r.a : r.b;
                int D = (pass & 2) == 0 ? r.b : r.a;

                if (A <= C && B <= D) return true;

                double qa = A * A + B * B, qb = -2 * C * B, qc = C * C - A * A;
                double det = qb * qb - 4 * qa * qc;
                const double EPS = 0.0001;

                if (det < -EPS) continue;
                if (det < EPS) det = 0; else det = Math.Sqrt(det);

                for (int sign = -1; sign <= 1; sign += 2) {
                    double si = (-qb + sign * det) / (2 * qa);
                    if (si < -EPS || si > 1 + EPS) continue;
                    if (si < EPS) si = 0;
                    if (si > 1 - EPS) si = 1;

                    double co = Math.Sqrt(1 - si * si);

                    double w = A * co + B * si;
                    double h = A * si + B * co;
                    if (w < C + EPS && h < D + EPS) {
                        return true;
                    }
                }
            }

            return false;
        }
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();

        Rect[] R = new Rect[N];
        for (int i = 0; i < N; i++) {
            R[i].a = input.NextInt();
            R[i].b = input.NextInt();
        }

        Array.Sort(R);

        int[] f = new int[N];
        int best = 0;

        for (int i = 0; i < N; i++) {
            f[i] = 1;
            for (int j = 0; j < i; j++)
                if (R[j].FitsOnto(R[i]) && f[j] + 1 > f[i])
                    f[i] = f[j] + 1;

            if (f[i] > best)
                best = f[i];
        }

        Console.WriteLine(best);
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
