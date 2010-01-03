import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	PrintWriter out;
	Scanner in;

	public void run() throws Exception {
		in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		for (;;) {
			String a = in.next("[\\-+0-9A-F]+");
			String b = in.next("[\\-+0-9A-F]+");

			a = a.replaceAll("\\+", "");
			b = b.replaceAll("\\+", "");

			BigInteger A = new BigInteger(a, 16);
			BigInteger B = new BigInteger(b, 16);
			if (A.compareTo(B) > 0) { BigInteger T = A; A = B; B = T; }

			BigInteger Z = new BigInteger("0");
			if (A.equals(Z) && B.equals(Z)) break;

			out.printf("%+X %+X\n%+X\n", A, B, A.add(B));
		}

		out.flush();
		out.close();
	}

	public static void main(String[] args) throws Exception {
		//Locale.setDefault(Locale.US);
		new Main().run();
		System.exit(0);
	}
}
