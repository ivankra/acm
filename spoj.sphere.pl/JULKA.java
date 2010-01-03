import java.math.*;
import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		for (int cs = 1; cs <= 10 && in.hasNextBigInteger(); cs++) {
			BigInteger a = in.nextBigInteger();
			BigInteger b = in.nextBigInteger();

			BigInteger x = a.add(b).divide(new BigInteger("2"));
			BigInteger y = a.subtract(x);

			System.out.printf("%s\n%s\n", x, y);
		}
	}
}
