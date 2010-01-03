using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    void flip(int[,] grid, int y, int x) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx != 0 && dy != 0) continue;
                if (0 <= y + dy && y + dy < 4 &&
                    0 <= x + dx && x + dx < 4)
                    grid[y + dy, x + dx] = 1 - grid[y + dy, x + dx];
            }
        }
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int[,] source = new int[4, 4];
        int[,] grid = new int[4, 4];

        for (int i = 0; i < 4; i++) {
            string s = input.Next();
            for (int j = 0; j < 4; j++)
                source[i, j] = (s[j] == 'w' ? 0 : 1);
        }

        int best = 999;

        for (int goal = 0; goal < 2; goal++) {
            for (int mask = 0; mask < 16; mask++) {
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                        grid[i, j] = source[i, j];
                
                int res = 0;
                
                for (int i = 0; i < 4; i++) {
                    if ((mask & (1 << i)) != 0) {
                        res++;
                        flip(grid, 0, i);
                    }
                }

                for (int row = 0; row < 4; row++) {
                    for (int col = 0; col < 4; col++) {
                        if (grid[row, col] != goal) {
                            if (row == 3)
                                res = 999;
                            else {
                                flip(grid, row + 1, col);
                                res++;
                            }
                        }
                    }
                }

                if (res < best)
                    best = res;
            }
        }

        if (best > 16)
            Console.WriteLine("Impossible");
        else
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
