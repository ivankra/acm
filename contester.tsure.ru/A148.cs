using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        long R = input.NextInt();
        long xc = input.NextInt();
        long yc = input.NextInt();
        long x = input.NextInt() - xc;
        long y = input.NextInt() - yc;
        long dx = input.NextInt() - xc - x;
        long dy = input.NextInt() - yc - y;

        long a = dx * dx + dy * dy;
        long b = 2 * x * dx + 2 * y * dy;
        long c = x * x + y * y - R * R;
        long det = b * b - 4 * a * c;

        if (det == 0)
            Console.WriteLine("0");
        else if (det < 0)
            Console.WriteLine("-1");
        else {
            double res = Math.Sqrt(det) / a * Math.Sqrt(dx * dx + dy * dy);
            Console.WriteLine("{0:0.00000000}", res);
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
