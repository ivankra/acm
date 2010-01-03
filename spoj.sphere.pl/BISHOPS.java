import java.util.*;
import java.math.*;

public class Main {
    public void run() {
        Scanner in = new Scanner(System.in);
        while (in.hasNextBigInteger()) {
            BigInteger N = in.nextBigInteger();
            if (N.compareTo(BigInteger.ONE) > 0) {
                BigInteger two = new BigInteger("2");
                N = N.multiply(two).subtract(two);
            }
            System.out.println(N);
        }
    }

    public static void main(String[] args) {
        (new Main()).run();
    }
}
