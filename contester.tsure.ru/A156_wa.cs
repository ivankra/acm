using System;
using System.Collections.Generic;
using System.Text;

public class Tree {
    int[] keys, count, size;

    void inc(int a, int b, int x, int by) {
        if (a > b) return;

        int c = (a + b) / 2;
        size[c] += by;

        if (keys[c] == x)
            count[c] += by;
        else if (x < keys[c])
            inc(a, c - 1, x, by);
        else
            inc(c + 1, b, x, by);
    }

    int treeSize(int a, int b) {
        return a <= b ? size[(a + b) / 2] : 0;
    }

    int find(int a, int b, int k) {
        int c = (a + b) / 2;
        if (k > size[c]) throw new Exception();
        if (k <= treeSize(a, c - 1)) {
            return find(a, c - 1, k);
        } else {
            k -= treeSize(a, c - 1);
            if (k == 1)
                return keys[c];
            return find(c + 1, b, k - 1);
        }
    }

    void traverse(int a, int b, List<int> res) {
        if (a > b) return;
        int c = (a + b) / 2;
        traverse(a, c - 1, res);
        for (int i = 0; i < count[c]; i++)
            res.Add(keys[c]);
        traverse(c + 1, b, res);
    }

    public int[] ToArray() {
        List<int> res = new List<int>();
        traverse(0, keys.Length - 1, res);
        return res.ToArray();
    }

    public void Add(int value) {
        inc(0, keys.Length - 1, value, 1);
    }

    public void Remove(int value) {
        inc(0, keys.Length - 1, value, -1);
    }

    public int Find(int k) {
        return find(0, keys.Length - 1, k);
    }

    public Tree(int[] keys_dup) {
        Array.Sort(keys_dup);

        List<int> temp = new List<int>();
        for (int i = 0; i < keys_dup.Length; i++)
            if (i == 0 || keys_dup[i] != keys_dup[i - 1])
                temp.Add(keys_dup[i]);

        this.keys = temp.ToArray();
        this.count = new int[keys.Length];
        this.size = new int[keys.Length];
    }
}

public class Program {
    void Run() {
        Scanner input = new Scanner(Console.In);

        int N = input.NextInt();
        char[] op = new char[N];
        int[] arg = new int[N];
        List<int> keys = new List<int>();

        for (int i = 0; i < N; i++) {
            string s = input.Next();
            op[i] = char.ToUpper(s[0]);
            arg[i] = input.NextInt();

            if (op[i] == 'P')
                keys.Add(arg[i]);

            if (op[i] != 'P' && op[i] != 'G')
                throw new Exception();
        }

        Tree tree = new Tree(keys.ToArray());
        for (int i = 0; i < N; i++) {
            if (op[i] == 'P') {
                tree.Add(arg[i]);
            } else {
                try {
                    tree.Remove(tree.Find(arg[i]));
                } catch (Exception e) {}
            }
        }

        int[] res = tree.ToArray();
        foreach (int i in res)
            Console.WriteLine(i);

        if (res.Length == 0)
            Console.WriteLine("empty");
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
