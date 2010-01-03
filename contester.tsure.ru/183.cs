using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

public class Program
{
    struct Point
    {
        public int x, y;

        public Point(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }

    void solve(string moves)
    {
        const int L = 20;
        Point[] worm = new Point[L];

        for (int i = 0; i < L; i++)
            worm[i] = new Point(25, 30 - i);

        for (int id = 1; id <= moves.Length; id++)
        {
            int dx = 0, dy = 0;
            switch (moves[id - 1])
            {
                case 'N': dx = -1; break;
                case 'S': dx = +1; break;
                case 'W': dy = -1; break;
                case 'E': dy = +1; break;
            }

            Point head = worm[0];
            Point newHead = new Point(head.x + dx, head.y + dy);

            if (newHead.x < 1 || newHead.x > 50 || newHead.y < 1 || newHead.y > 50)
            {
                Console.WriteLine("The worm ran off the board on move {0}.", id);
                return;
            }

            for (int i = 1; i < L-1; i++) {
                Point p = worm[i];
                if (p.x == newHead.x && p.y == newHead.y)
                {
                    Console.WriteLine("The worm ran into itself on move {0}.", id);
                    return;
                }
            }

            for (int i = L-1; i >= 1; --i)
                worm[i] = worm[i - 1];
            worm[0] = newHead;
        }

        Console.WriteLine("The worm successfully made all {0} moves.", moves.Length);
    }

    void Run()
    {
        Scanner input = new Scanner(Console.In);

        while (input.HasNext())
        {
            int N = input.NextInt();
            if (N == 0) break;

            string moves = input.Next();
            solve(moves);
        }
    }

    class Scanner
    {
        TextReader reader;
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
