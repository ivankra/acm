import java.util.*;
import java.math.*;

public class Main {
    static class Rational {
        BigInteger p, q;

        public Rational(BigInteger p_, BigInteger q_) {
            p = p_;
            q = q_;
            reduce();
        }

        public Rational(long p_, long q_) {
            p = new BigInteger("" + p_);
            q = new BigInteger("" + q_);
            reduce();
        }

        void reduce() {
            if (q.compareTo(BigInteger.ZERO) < 0) {
                p = p.negate();
                q = q.negate();
            }

            BigInteger g = p.gcd(q);
            p = p.divide(g);
            q = q.divide(g);
        }

        Rational add(Rational x) {
            BigInteger P = p.multiply(x.q).add(x.p.multiply(q));
            BigInteger Q = q.multiply(x.q);
            return new Rational(P, Q);
        }

        Rational sub(Rational x) {
            BigInteger P = p.multiply(x.q).subtract(x.p.multiply(q));
            BigInteger Q = q.multiply(x.q);
            return new Rational(P, Q);
        }

        Rational multiply(Rational x) {
            return new Rational(p.multiply(x.p), q.multiply(x.q));
        }

        void divideBy(long n) {
            q = q.multiply(new BigInteger("" + n));
            reduce();
        }
    }

    Rational f(long n) {
        Rational part1 = new Rational(0, 1);
        if (n <= 6) {
            for (long k = 1; k <= n; k++) {
                part1 = part1.add(new Rational(1, k));
                part1 = part1.sub(new Rational(1, k+3));
            }
        } else {
            for (long k = 1; k <= 3; k++)
                part1 = part1.add(new Rational(1, k));
            for (long k = n+1; k <= n+3; k++)
                part1 = part1.sub(new Rational(1, k));
        }
        part1.divideBy(6);

        Rational part2 = new Rational(0, 1);
        if (n <= 3) {
            for (long k = 1; k <= n; k++) {
                part2 = part2.add(new Rational(1, k+2));
                part2 = part2.sub(new Rational(1, k+1));
            }
        } else {
            part2 = new Rational(1, n+2);
            part2 = part2.sub(new Rational(1, 2));
        }
        part2.divideBy(2);

        return part1.add(part2);
    }

    public void run() {
        Scanner in = new Scanner(System.in);
        for (int cs = 1;; cs++) {
            long n = in.nextLong();
            long m = in.nextLong();
            if (n == 0 && m == 0) break;

            Rational result = f(n).multiply(f(m));
            String p = result.p.toString();
            String q = result.q.toString();

            System.out.printf("Case %d:\n", cs);
            System.out.println(p);
            for (int i = 0; i < p.length() || i < q.length(); i++)
                System.out.print('-');
            System.out.println();
            System.out.println(q);
            System.out.println();
        }
    }

    public static void main(String[] args) {
        (new Main()).run();
    }
}
