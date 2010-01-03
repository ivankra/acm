import java.io.*;
import java.util.*;
import java.math.*;

public class $CLASSNAME$ {
    public $RETURNTYPE$ $METHODNAME$($METHODPARAMS$) {

    }

// BEGIN CUT HERE
    // Converts object (recursively) to a string in format similar to the one,
    // used in TopCoder's problem statements.
    static String tc_toString(Object x) {
        if (x == null) return "null";
        if (x instanceof String) return "\"" + (String)x + "\"";

        if (x.getClass().isArray()) {
            int n = java.lang.reflect.Array.getLength(x);
            StringBuilder s = new StringBuilder("{");
            for (int i = 0; i < n; i++) {
                if (i > 0) s.append(", ");
                s.append(tc_toString(java.lang.reflect.Array.get(x, i)));
            }
            s.append("}");
            return s.toString();
        }

        if (x instanceof Double) {
            String s = String.format("%.10f", x);
            while (s.endsWith("0") && !s.endsWith(".0"))
                s = s.substring(0, s.length() - 1);
            return s;
        }

        return x.toString();
    }

    // Verifies program's output against expected output.
    static boolean tc_equals(Object result, Object expected) {
        if (!expected.getClass().equals(result.getClass()))
            return false;

        if (expected instanceof Double) {
            double x = (Double)expected;
            double y = (Double)result;

            double eps = 1E-9;

            if (Double.isNaN(x)) {
                return Double.isNaN(y);
            } else if (Double.isInfinite(x)) {
                if (x > 0)
                    return y > 0 && Double.isInfinite(y);
                else
                    return y < 0 && Double.isInfinite(y);
            } else if (Double.isNaN(y) || Double.isInfinite(y)) {
                return false;
            } else if (Math.abs(y - x) < eps) {
                return true;
            } else {
                double min = Math.min(x * (1.0 - eps), x * (1.0 + eps));
                double max = Math.max(x * (1.0 - eps), x * (1.0 + eps));
                return min < y && y < max;
            }
        }

        if (expected.getClass().isArray()) {
            int n = java.lang.reflect.Array.getLength(result);
            int m = java.lang.reflect.Array.getLength(expected);
            if (n != m)
                return false;

            for (int i = 0; i < n; i++) {
                Object x = java.lang.reflect.Array.get(result, i);
                Object y = java.lang.reflect.Array.get(expected, i);
                if (!tc_equals(x, y)) return false;
            }

            return true;
        }

        return expected.equals(result);
    }

    static boolean tc_runEx(Object[] example) {
        String id = (String)example[0];
        Object[] input = (Object[])example[1];
        Object answer = example[2];

        Object result;
        try {
            $CLASSNAME$ instance = new $CLASSNAME$();
            $IODECL$
        } catch (Exception e) {
            if (id.length() > 0)
                System.out.printf("%s: ", id);
            System.out.printf("Exception occurred\n");
            System.out.printf("Input: %s\n", tc_toString(input));
            if (answer != null)
                System.out.printf("Expected:  %s\n", answer);
            e.printStackTrace(System.out);
            System.out.println();
            return false;
        }

        if (id.length() > 0)
            System.out.printf("%s: ", id);

        if (answer != null) {
            if (!tc_equals(result, answer)) {
                System.out.printf("WRONG ANSWER\n");
                System.out.printf("Input: %s\n", tc_toString(input));
                System.out.printf("Received: %s\n", tc_toString(result));
                System.out.printf("Expected: %s\n\n", tc_toString(answer));
                return false;
            } else {
                String s1 = tc_toString(result);
                String s2 = tc_toString(answer);
                if (s1.equals(s2))
                    System.out.printf("OK\n\n");
                else
                    System.out.printf("OK (result=%s expected=%s)\n\n", s1, s2);
            }
            return true;
        } else {
            System.out.printf("Input: %s\n", tc_toString(input));
            System.out.printf("Received: %s\n\n", tc_toString(result));
            return true;
        }
    }

    static void tc_run(Object... args) {
        tc_runEx(new Object[]{"", null, args});
    }

    public static void main(String[] args) {
        Object[][] examples = new Object[][] {
// id, arguments, answer
$EXAMPLES$

        };

        // running your own tests:
        //   tc_run(argument1, argument2, ...);
        // or add a test case to the above table.

        if (args.length == 0) {
            for (Object[] e : examples) tc_runEx(e);
        } else {
            for (String s : args) {
                for (Object[] e : examples) {
                    String id = (String)e[0];
                    if (id.equals(s) || id.equals("Example " + s)) tc_runEx(e);
                }
            }
        }
    }
// END CUT HERE
}
