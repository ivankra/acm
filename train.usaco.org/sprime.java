/*
ID: infnty1
PROB: sprime
LANG: JAVA
*/
import java.io.*;
import java.util.*;

class sprime {
	static boolean isPrime(int n) {
		if (n <= 1 || (n > 2 && (n & 1) == 0)) return false;
		for (int d = 3; (d * d) <= n; d += 2)
			if ((n % d) == 0) return false;
		return true;
	}

	static void rec(PrintWriter out, int a, int n) {
		if (n == 0 && isPrime(a))
			out.printf("%d\n", a);
		else
			for (int i = 1; i <= 9; i += 2)
				if (isPrime(a*10+i)) rec(out, a*10+i, n-1);
	}

	public static void main(String[] args) throws Exception {
		PrintWriter out = new PrintWriter(new FileWriter("sprime.out"));
		int n = (new Scanner(new FileReader("sprime.in"))).nextInt();

		for (int i = 1; i < 10; i++)
			if (isPrime(i)) rec(out, i, n - 1);

		out.close();
		System.exit(0);
	}
}
