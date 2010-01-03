using System;

public class Program {
    int height, width;
    string[] mat;
    int[,] killer;

    int OddSquare() {
        killer = new int[height, width];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                killer[i, j] = 1;

        int best = -1;
        for (int size = 1; size+2 <= height && size+2 <= width; size += 2) {
            int half = (size + 1) / 2;
            for (int y = half; y < height - half; y++) {
                for (int x = half; x < width - half; x++) {
                    if (killer[y, x] != size)
                        continue;

                    for (int i = -half; i <= half; i++)
                        if (mat[y - half][x + i] != mat[y + half][x - i]) goto stop;

                    for (int i = -half; i <= half; i++)
                        if (mat[y - i][x - half] != mat[y + i][x + half]) goto stop;

                    killer[y, x] += 2;
                    best = Math.Max(best, killer[y, x]);

                stop: ;
                }
            }
        }

        return best;
    }

    int EvenSquare() {
        killer = new int[height, width];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                killer[i, j] = 0;

        int best = -1;
        for (int size = 0; size+2 <= height && size+2 <= width; size += 2) {
            int half = size / 2 + 1;
            for (int y = half; y <= height - half; y++) {
                for (int x = half; x <= width - half; x++) {
                    if (killer[y, x] != size)
                        continue;

                    for (int i = -half + 1; i <= half; i++)
                        if (mat[y - half][x - i] != mat[y + half - 1][x + i - 1]) goto stop;

                    for (int i = -half + 1; i <= half; i++)
                        if (mat[y - i][x - half] != mat[y + i - 1][x + half - 1]) goto stop;

                    killer[y, x] += 2;
                    best = Math.Max(best, killer[y, x]);

                stop: ;
                }
            }
        }

        return best;
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        height = input.NextInt();
        width = input.NextInt();

        mat = new string[height];
        for (int i = 0; i < height; i++)
            mat[i] = input.Next();

        int best = Math.Max(OddSquare(), EvenSquare());
        Console.WriteLine(best);
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
