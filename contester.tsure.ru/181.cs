using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

public class Program
{
    public void Run() {
        Scanner input = new Scanner(Console.In);

        double height = input.NextDouble();

        double[] x = new double[200];
        double[] y = new double[200];

        int n = input.NextInt() + 1;
        for (int i = 0; i < n; i++)
        {
            x[i] = input.NextDouble();
            y[i] = input.NextDouble();
        }

        int m = input.NextInt() + 1;
        n += m;
        for (int i = 1; i <= m; i++)
        {
            x[n - i] = input.NextDouble();
            y[n - i] = input.NextDouble();
        }

        double area = 0;
        for (int i = 0; i < n; i++)
        {
            int j = (i + 1) % n;
            area += x[i] * y[j] - x[j] * y[i];
        }

        double volume = Math.Abs(area) / 2.0 * height;
        Console.WriteLine("{0:0.00}", volume);
    }

    public class Scanner
    {
        TextReader reader;
        char[] sep = new char[] { ' ', '\t', '\n', '\r' };
        string[] tok = new string[] { };
        int tokp = 0;

        private bool update()
        {
            while (tokp >= tok.Length)
            {
                string line = reader.ReadLine();
                if (line == null)
                    return false;
                tok = line.Split(sep, StringSplitOptions.RemoveEmptyEntries);
                tokp = 0;
            }
            return true;
        }

        public Scanner(TextReader reader) { this.reader = reader; }
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
