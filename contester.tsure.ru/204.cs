using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    class Vertex {
        public double x, y;
        public double heading;
        public Vertex parent;

        public double DistanceTo(Vertex v) {
            if (v == null) return 0;
            return Math.Sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
        }

        public override string ToString() {
            return string.Format("({0:0.000}, {1:0.000})", x, y);
        }
    }

    Vertex AA, BB;
    Vertex A = null, B = null, root;
    double K;

    // garbage collecting is really handy here...
    void snowflake(Vertex u, int N, double L) {
        if (N == 0) {
            if (A == null || AA.DistanceTo(u) < AA.DistanceTo(A)) A = u;
            if (B == null || BB.DistanceTo(u) < BB.DistanceTo(B)) B = u;
            return;
        }

        for (int i = 0; i < 6; i++) {
            if (i == 3 && u.parent != null) continue;

            Vertex v = new Vertex();
            v.heading = u.heading + Math.PI * i / 3.0;
            v.x = u.x + L * Math.Cos(v.heading);
            v.y = u.y + L * Math.Sin(v.heading);
            v.parent = u;

            snowflake(v, N - 1, L / K);
        }
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        double L = input.NextDouble();
        K = input.NextDouble();

        AA = new Vertex();
        AA.x = input.NextDouble();
        AA.y = input.NextDouble();

        BB = new Vertex();
        BB.x = input.NextDouble();
        BB.y = input.NextDouble();

        root = new Vertex();
        root.x = 0;
        root.y = 0;
        root.heading = Math.PI / 2;
        root.parent = null;

        snowflake(root, N, L);

        double res = 0;
        while (A != B) {
            res += A.DistanceTo(A.parent);
            res += B.DistanceTo(B.parent);
            A = A.parent;
            B = B.parent;
        }

        Console.WriteLine("{0:0.00000}", res);
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
