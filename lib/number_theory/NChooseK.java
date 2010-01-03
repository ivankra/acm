import java.math.*;

public class Main {
    BigInteger choose(int n, int k) {
        if (k < 0 || k > n) return BigInteger.ZERO;
        if (n-k < k) k = n-k;

        BigInteger x = BigInteger.ONE;
        for (int i = 1; i <= k; i++) {
            x = x.multiply(new BigInteger(""+(n-i+1)));
            x = x.divide(new BigInteger(""+i));
        }

        return x;
    }
}
