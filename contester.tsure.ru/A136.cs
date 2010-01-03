using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    const double EPS = 1e-9;

    struct Rect {
        public double x1, x2, y;
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        Rect[] R = new Rect[N];
        double[] xs = new double[2 * N];

        for (int i = 0; i < N; i++) {
            R[i].x1 = input.NextDouble();
            R[i].x2 = R[i].x1 + input.NextDouble();
            R[i].y = input.NextDouble();

            if (R[i].x2 - R[i].x1 < EPS || R[i].y < EPS)
                throw new Exception();

            xs[2 * i] = R[i].x1;
            xs[2 * i + 1] = R[i].x2;
        }

        Array.Sort(xs);

        double[,] curve = new double[10 * N, 2];
        int K = 1;
        curve[0, 0] = xs[0];
        curve[0, 1] = 0;

        for (int i = 0; i < 2 * N - 1; i++) {
            double x1 = xs[i];
            double x2 = xs[i + 1];
            if (x2 - x1 < EPS) continue;

            double y = 0;
            foreach (Rect r in R) {
                if (r.x1 < x1 + EPS && x2 - EPS < r.x2) {
                    y = Math.Max(y, r.y);
                }
            }

            curve[K, 0] = x1;
            curve[K, 1] = y;
            curve[K+1, 0] = x2;
            curve[K+1, 1] = y;
            K += 2;
        }

        curve[K, 0] = xs[2 * N - 1];
        curve[K, 1] = 0;
        K++;

        for (int pass = 0; pass < 2; pass++) {
            int count = 0;
            for (int i = 0; i < K; i++) {
                if (0 < i && i < K - 1) {
                    if (Math.Abs(curve[i, 1] - curve[i - 1, 1]) < EPS &&
                        Math.Abs(curve[i + 1, 1] - curve[i, 1]) < EPS)
                        continue;
                }
                if (pass == 0)
                    count++;
                else
                    Console.WriteLine("{0:0.00000000} {1:0.00000000}", curve[i, 0], curve[i, 1]);
            }
            if (pass == 0)
                Console.WriteLine(count);
        }
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
