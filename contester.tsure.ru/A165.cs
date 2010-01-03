using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    int[] ReadConfig(Scanner input, int N) {
        int[] v = new int[N];
        for (int i = 0; i < N; i++) {
            int y = input.NextInt();
            int x = input.NextInt();
            v[i] = (y - 1) * 4 + (x - 1);
        }
        Array.Sort(v);
        return v;
    }

    int Encode(int[] v) {
        int res = 0;
        for (int i = 0; i < v.Length; i++)
            res = (res << 8) + v[i];
        return res;
    }

    void Decode(int[] v, int e) {
        for (int i = v.Length - 1; i >= 0; --i, e >>= 8)
            v[i] = e & 255;
    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        int maxMoves = input.NextInt();

        int[] source = ReadConfig(input, N);
        int goal = Encode(ReadConfig(input, N));

        Dictionary<int, int> dist = new Dictionary<int, int>();
        Queue<int> Q = new Queue<int>();

        Q.Enqueue(Encode(source));
        dist.Add(Encode(source), 0);

        int[] state = new int[N];
        int[] temp = new int[N];

        while (Q.Count != 0) {
            int stateEnc = Q.Dequeue();
            if (stateEnc == goal) {
                Console.WriteLine("YES");
                return;
            }

            if (dist[stateEnc] >= maxMoves)
                continue;

            Decode(state, stateEnc);

            for (int p = 0; p < N; p++) {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx != 0 && dy != 0) continue;
                        if (dx == 0 && dy == 0) continue;

                        for (int mul = 1; mul <= 2; mul++) {
                            int y = (state[p] / 4) + mul * dy;
                            int x = (state[p] % 4) + mul * dx;
                            if (y < 0 || y >= 4 || x < 0 || x >= 4) continue;

                            int t = y * 4 + x;

                            bool ok = true;
                            for (int i = 0; i < N; i++)
                                if (t == state[i]) ok = false;
                            if (!ok) continue;

                            for (int i = 0; i < N; i++) temp[i] = state[i];
                            temp[p] = t;
                            Array.Sort(temp);

                            int tempEnc = Encode(temp);

                            if (!dist.ContainsKey(tempEnc)) {
                                dist.Add(tempEnc, dist[stateEnc] + 1);
                                Q.Enqueue(tempEnc);
                            }
                            
                            break;
                        }
                    }
                }
            }
        }

        Console.WriteLine("NO");
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
