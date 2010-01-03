import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
	long[][] C;

	private BigInteger doit(ArrayList<Integer> tree) {
		if (tree.size() <= 1)
			return BigInteger.ONE;

		ArrayList<Integer> left = new ArrayList();
		ArrayList<Integer> right = new ArrayList();

		int root = tree.get(0);
		for (int i = 1; i < tree.size(); i++) {
			int x = tree.get(i);
			if (x < root) left.add(x);
			if (x > root) right.add(x);
		}

		BigInteger a = doit(left);
		BigInteger b = doit(right);
		BigInteger c = new BigInteger("" + C[tree.size()-1][left.size()]);
		return a.multiply(b).multiply(c);
	}

	public void run() throws Exception {
		Scanner in = new Scanner(System.in);
		PrintWriter out = new PrintWriter(System.out);

		C = new long[32][32];
		for (int n = 0; n < 32; n++) {
			C[n][0] = 1;
			for (int k = 1; k <= n; k++) {
				C[n][k] = C[n-1][k-1] + C[n-1][k];
			}
		}

		int T = in.nextInt();
		for (int cs = 1; cs <= T; cs++) {
			int N = in.nextInt();

			ArrayList<Integer> tree = new ArrayList();
			for (int i = 0; i < N; i++) {
				tree.add(in.nextInt());
			}

			BigInteger res = doit(tree);
			out.println(res);
		}

		out.close();
	}

	public static void main(String[] args) throws Exception {
		new Main().run();
	}
}
