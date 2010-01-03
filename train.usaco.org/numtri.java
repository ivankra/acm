/*
ID: infnty1
PROB: numtri
LANG: JAVA
*/
import java.io.*;
import java.util.*;

class numtri {
	public static void main(String[] args) throws Exception {
		Scanner in = new Scanner(new BufferedReader(new FileReader("numtri.in")));
		PrintWriter out = new PrintWriter(new FileWriter("numtri.out"));
		int[] a, b, c;
		int i, j, k, r;

		r = in.nextInt();

		a = new int[r+1];
		b = new int[r+1];

		a[0] = 0;
		for (i = 1; i <= r; i++) {
			b[0] = in.nextInt() + a[0];
			for (j = 1; j < i; j++)
				b[j] = Math.max(a[j-1], a[j]) + in.nextInt();
			c = a; a = b; b = c;
		}

		for (j = a[0], i = 1; i < r; i++)
			j = Math.max(j, a[i]);

		out.printf("%d\n", j);
		out.close();
		System.exit(0);
	}
}
