/*
ID: infnty1
PROB: frac1
LANG: JAVA
*/
import java.io.*;
import java.util.*;

class frac1 {
	static PrintWriter out;
	static int n;

	static void f(int a, int b, int c, int d) {
		int p = a + c, q = b + d;
		if (q <= n) {
			f(a, b, p, q);
			out.printf("%d/%d\n", p, q);
			f(p, q, c, d);
		}
	}

	public static void main(String[] args) throws Exception {
		n = (new Scanner(new FileReader("frac1.in"))).nextInt();
		out = new PrintWriter(new BufferedWriter(new FileWriter("frac1.out")));
		out.printf("0/1\n");
		f(0,1, 1,1);
		out.printf("1/1\n");
		out.close();
		System.exit(0);
	}
}
