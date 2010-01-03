using System;
using System.Collections.Generic;
using System.Text;

public class Program {
    int qsort(int[] a, int left, int right) {
        int key = a[(left + right) / 2];
        int i = left;
        int j = right;

       /* Console.Write("qsort left={0} right={1}: ", left, right);
        for (int k = left; k <= right; ++k) Console.Write("{0} ", a[k]);
        Console.WriteLine(" key={0}", key);*/
        
        int res = 0;
        do {
            while (a[i] < key) { i++; res++; } res++;
            while (key < a[j]) { j--; res++; } res++;

            if (i <= j) {
                int t = a[i]; a[i] = a[j]; a[j] = t;
                i++;
                j--;
            }
        } while (i <= j);

        /*Console.Write("  i={0} j={1} {2}: ", i, j, res);
        for (int k = left; k <= right; ++k) Console.Write("{0} ", a[k]);
        Console.WriteLine();*/

        if (left < j)
            res += qsort(a, left, j);

        if (i < right)
            res += qsort(a, i, right);
        
        return res;
    }

    int best_c;

    void rec(int[] a, int i, int N) {
        if (i > N) {
            int[] b = new int[N+1];
            Array.Copy(a, b, N + 1);

            int c = qsort(b, 1, N);
            if (c >= best_c) {
                best_c = c;
                for (int k = 1; k<= N; k++) Console.Write("{0} ", a[k]);
                Console.WriteLine(": {0}", c);
            }
            return;
        }

        for (a[i] = 1; a[i] <= N; a[i]++) {
            for (int j = 1; j < i; j++) if (a[j] == a[i]) goto skip;
            rec(a, i + 1, N);
        skip:
            ;
        }

    }

    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        if (N <= 4) {
            string[] sol = new string[] { "1", "1 2", "1 3 2", "1 4 2 3" };
            Console.WriteLine(sol[N]);
        } else {
            int[] a = new int[N + 10];
            a[1] = 1;
            a[2] = 4;
            a[3] = 2;
            a[4] = 3;
            for (int K = 5; K <= N; K++) {
                int p = (1 + K) / 2;
                a[K] = a[p];
                a[p] = K;
            }

            for (int i = 1; i <= N; i++)
                Console.Write("{0} ", a[i]);
            Console.WriteLine();
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
