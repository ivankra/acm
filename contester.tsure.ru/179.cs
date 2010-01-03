using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

public class Program
{
    public class Scanner {
        TextReader reader;
        char[] sep = new char[] { ' ', '\t', '\n', '\r' };
        string[] tok = new string[] { };
        int tokp = 0;

        private bool update() {
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
    }

    struct Point
    {
        public int y, x;
    }

    string[] map;
    uint[,] dist;
    const uint INF = 0xFFFFFFFF;

    public void Run() {
        Scanner input = new Scanner(Console.In);

        int height = input.NextInt();
        int width = input.NextInt();

        Point start, goal;
        start.y = input.NextInt() - 1;
        start.x = input.NextInt() - 1;
        goal.y = input.NextInt() - 1;
        goal.x = input.NextInt() - 1;

        map = new string[height];
        for (int i = 0; i < height; i++)
            map[i] = input.Next();

        dist = new uint[height, width];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                dist[i, j] = INF;

        dist[start.y, start.x] = 1;

        Queue<Point> Q1 = new Queue<Point>(height * width);
        Queue<Point> Q2 = new Queue<Point>(height * width);
        Q1.Enqueue(start);

        while (Q1.Count != 0) {
            Q2.Enqueue(Q1.Dequeue());
            while (Q2.Count != 0) {
                Point s = Q2.Dequeue();

                if (s.y == goal.y && s.x == goal.x) {
                    uint res = dist[s.y, s.x];
                    Console.WriteLine("{0} {1}", res & 65535, res >> 16);
                    return;
                }

                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        if (dx == 0 && dy == 0) continue;

                        Point t;
                        t.y = s.y + dy;
                        t.x = s.x + dx;

                        if (t.y < 0 || t.y >= height) continue;
                        if (t.x < 0 || t.x >= width) continue;
                        if (map[t.y][t.x] == '0') continue;

                        if (map[t.y][t.x] == map[s.y][s.x] && dist[s.y, s.x] + 1 < dist[t.y, t.x]) {
                            dist[t.y, t.x] = dist[s.y, s.x] + 1;
                            Q2.Enqueue(t);
                        } else if (map[t.y][t.x] != map[s.y][s.x] && dist[s.y, s.x] + 65537 < dist[t.y, t.x]) {
                            dist[t.y, t.x] = dist[s.y, s.x] + 65537;
                            Q1.Enqueue(t);
                        }
                    }
                }
            }
        }

        Console.WriteLine("0 0");
    }

    public static void Main(string[] args) { new Program().Run(); }
}
