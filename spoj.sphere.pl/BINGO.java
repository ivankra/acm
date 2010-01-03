import java.io.*;
import java.util.*;

public class Main {
    String next() throws IOException {
        StringBuilder sb = new StringBuilder();
        while (true) {
            int ch = System.in.read();
            if (ch == -1) break;
            if (Character.isLetter(ch))
                sb.append((char)ch);
            else if (sb.length() != 0)
                break;
        }
        return sb.length() == 0 ? null : sb.toString();
    }

    long gcd(long x, long y) {
        return y == 0 ? x : gcd(y, x%y);
    }

    public void run() throws IOException {
        long num = 0, den = 0;
        HashSet<String> set = new HashSet<String>();

        while (true) {
            String s = next();
            if (s == null) break;

            if (s.equals("BULLSHIT")) {
                num += set.size();
                den++;
                set.clear();
            } else {
                set.add(s.toLowerCase());
            }
        }

        long g = gcd(num, den);
        if (g == 0) { num = 1; den = 0; g = 1; }
        System.out.printf("%d / %d\n", num/g, den/g);
    }

    public static void main(String args[]) throws IOException {
        new Main().run();
    }
}
