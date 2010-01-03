
// BEGIN CUT HERE
class Tester {
    public static void Main(string[] args) {
        //Run(arg1, arg2, ...);  or  RunAns(arg1, ..., answer);
        RunExamples(args);
        PrintSummary();
        Console.ReadKey();
    }
#region Testing code

    static Example[] examples = {
$EXAMPLES$    };

    static void RunExamples(string[] args) {
        if (args.Length == 0) {
            foreach (Example e in examples) {
            	RunExample(e);
            }
        } else {
            foreach (string s in args) {
            	int n = -1;
            	try { n = int.Parse(s); } catch (Exception) { n = -1; }
            	if (0 <= n && n < examples.Length) {
            	    RunExample(examples[n]);
                } else {
            	    Console.WriteLine("{0}: bad test id", s);
            	}
            }
        }
    }

    public static void PrintSummary() {
        Console.WriteLine();
        if (numPassed == numTotal)
            Console.Write("--- All tests OK ---\n");
        else if (numFailed > 0)
            ColorWrite(ConsoleColor.Yellow, "--- FAILED ---\n");
    }

    class Example {
        public string id;
        public object[] input;
        public object answer;

        public Example(string id, object[] input, object answer) {
            this.id = id;
            this.input = input;
            this.answer = answer;
        }
    }

    static bool Verify(object result, object expected) {
        if (!result.GetType().Equals(expected.GetType())) {
            // int->long and long->double casts
            if (result is int) return Verify((long)((int)result), expected);
            if (expected is int) return Verify(result, (long)((int)expected));
            if ((result is double) || (expected is double)) {
                if (result is long) return Verify((double)((long)result), expected);
                if (expected is long) return Verify(result, (double)((long)expected));
            }
            return false;
        }

        if (expected is double) {
            double x = (double)expected;
            double y = (double)result;

            const double eps = 1E-9;

            if (double.IsNaN(x)) {
                return double.IsNaN(y);
            } else if (double.IsInfinity(x)) {
                if (x > 0)
                    return y > 0 && double.IsInfinity(y);
                else
                    return y < 0 && double.IsInfinity(y);
            } else if (double.IsNaN(y) || double.IsInfinity(y)) {
                return false;
            } else if (Math.Abs(y - x) < eps) {
                return true;
            } else {
                double min = Math.Min(x * (1.0 - eps), x * (1.0 + eps));
                double max = Math.Max(x * (1.0 - eps), x * (1.0 + eps));
                return min < y && y < max;
            }
        }

        if (expected is Array) {
            Array r = (Array)result;
            Array e = (Array)expected;
            if (e.Length != r.Length)
                return false;
            for (int i = 0; i < e.Length; i++)
                if (!Verify(r.GetValue(i), e.GetValue(i))) return false;
            return true;
        }

        return expected.Equals(result);
    }

    static string ToTopCoderString(object x) {
        if (x == null) {
            return "null";
        } else if (x is string) {
            // TODO: escape backslashes and quotes?
            return "\"" + (string)x + "\"";
        } else if (x is Array) {
            Array a = (Array)x;
            System.Text.StringBuilder s = new System.Text.StringBuilder("{");
            for (int i = 0; i < a.Length; i++) {
                if (i != 0) s.Append(", ");
                s.Append(ToTopCoderString(a.GetValue(i)));
            }
            s.Append("}");
            return s.ToString();
        } else {
            return x.ToString();
        }
    }

    static string ToTopCoderString2(object x) {
        string s = ToTopCoderString(x);
        if (s.Length >= 2 && s[0] == '{' && s[s.Length - 1] == '}')
            return s.Substring(1, s.Length - 2);
        else
            return s;
    }

    static object DeepClone(object o) {
        if (o is Array) {
            Array a = o as Array;
            Array b = (Array)a.Clone();
            for (int i = 0; i < b.Length; i++) {
                b.SetValue(DeepClone(b.GetValue(i)), i);
            }
            return b;
        } else if (o is ICloneable) {
            return (o as ICloneable).Clone();
        } else {
            return o;
        }
    }

    static void ColorWrite(ConsoleColor color, string format, params object[] args) {
        ConsoleColor old = Console.ForegroundColor;
        Console.ForegroundColor = color;
        Console.Write(format, args);
        Console.ForegroundColor = old;
    }

    static int numFailed = 0, numPassed = 0, numTotal = 0;

    static bool RunExample(Example ex) {
        numTotal++;

        System.Diagnostics.Stopwatch timer = new System.Diagnostics.Stopwatch();
        timer.Start();

        object result = null;
        try {
            object[] input = (object[])DeepClone(ex.input);
$CLASSNAME$ instance = new $CLASSNAME$();
$IODECL$
        } catch (Exception e) {
            if (ex.id.Length > 0)
                Console.Write("{0}: ", ex.id);
            ColorWrite(ConsoleColor.Red, "Exception thrown\n");
            Console.Write("Input: {0}\n", ToTopCoderString2(ex.input));
            if (ex.answer != null)
                Console.Write("Expected: {0}\n", ToTopCoderString(ex.answer));
            Console.Write("{0}\n\n", e.ToString());
            numFailed++;
            return false;
        }

        timer.Stop();

        if (ex.id.Length > 0)
            Console.Write("{0}: ", ex.id);

        if (ex.answer == null) {
            // didn't crash
            Console.Write("Elapsed: {0} ms\n", timer.ElapsedMilliseconds);
            Console.Write("Input: {0}\n", ToTopCoderString2(ex.input));
            Console.Write("Received: {0}\n\n", ToTopCoderString(result));
            return true;
        } else if (!Verify(result, ex.answer)) {
            // WA
            ColorWrite(ConsoleColor.Red, "WRONG ANSWER");
            Console.Write(" [{0} ms]\n", timer.ElapsedMilliseconds);
            Console.Write("Input: {0}\n", ToTopCoderString2(ex.input));
            Console.Write("Received: {0}\n", ToTopCoderString(result));
            Console.Write("Expected: {0}\n\n", ToTopCoderString(ex.answer));
            numFailed++;
            return false;
        } else {
            ColorWrite(ConsoleColor.Green, "OK");
            Console.Write(" [{0} ms]\n\n", timer.ElapsedMilliseconds);
            numPassed++;
            return true;
        }
    }

    static bool Run(params object[] args) {
        return RunExample(new Example("", args, null));
    }

    static bool RunAns(params object[] a) {
        object[] args = new object[a.Length - 1];
        for (int i = 0; i < a.Length - 1; i++)
       	    args[i] = a[i];
        object answer = a[a.Length - 1];
        return RunExample(new Example("", args, answer));
    }
#endregion
}
// END CUT HERE
