using System;
using System.Text;

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        int height = input.NextInt();
        int width = input.NextInt();
        int N = 0;
        int[] vy = new int[200];
        int[] vx = new int[200];

        for (int y = 0; y < height; y++) {
            string line = input.Next();
            for (int x = 0; x < width; x++) {
                if (line[x] == '*') {
                    vy[N] = y;
                    vx[N] = x;
                    N++;
                }
            }
        }

        int ans = 0;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int w = int.MaxValue;
                for (int i = 0; i < N; ++i) {
                    int t = Math.Abs(vx[i] - x) + Math.Abs(vy[i] - y);
                    if (t < w) w = t;
                }

                if (w > ans) ans = w;
            }
        }

        Console.WriteLine(ans);
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
