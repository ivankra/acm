/*
ID: infnty1
PROB: pprime
LANG: JAVA
*/
import java.io.*;
import java.util.*;

class pprime {
	static boolean isPrime(int n) {
		int d;
		if (n <= 1) return false;
		for (d = 2; (d * d) <= n; d++)
			if ((n % d) == 0) return false;
		return true;		
	}

	static int rev(int n) {
		int r;
		for (r = 0; n > 0; n /= 10) r = r * 10 + (n % 10);
		return r;
	}

	static void solve(PrintWriter out, int a, int b) {
		SortedSet<Integer> s = new TreeSet<Integer>();
		int i, x, f, k, m;

		for (f = 0, m = 1, k = 0;; f++) {
			if (f >= m) {
				m *= 10;
				k++;
			}
			if (k > 4) break;
			
			x = f * m + rev(f);
			if (isPrime(x) && a <= x && x <= b) s.add(x);

			if (k >= 4) continue;

			for (i = 0; i <= 9; i++) {
				x = f * m * 10 + i * m + rev(f);
				if (isPrime(x) && a <= x && x <= b) s.add(x);
			}
		}

		for (int y : s)
			out.printf("%d\n", y);
	}

	public static void main(String[] args) throws Exception {
		Scanner in = new Scanner(new FileReader("pprime.in"));
		PrintWriter out = new PrintWriter(new FileWriter("pprime.out"));
		int a, b;

		a = in.nextInt();
		b = in.nextInt();

		solve(out, a, b);

		out.close();
		System.exit(0);
	}
}

