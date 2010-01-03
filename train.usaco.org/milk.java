/*
ID: infnty1
PROB: milk
LANG: JAVA
*/
import java.io.*;
import java.util.*;

class rec implements Comparable<rec> {
	public int p, a;

	public int compareTo(rec q) {
		return p - q.p;
	}
};

class milk {

	public static void main(String[] args) throws Exception {
		Scanner in = new Scanner(new BufferedReader(new FileReader("milk.in")));
		PrintWriter out = new PrintWriter(new FileWriter("milk.out"));
		rec[] r;
		int i, j, n, m, c;

		n = in.nextInt();
		m = in.nextInt();
		r = new rec[m];

		for (i = 0; i < m; i++) {
			r[i] = new rec();
			r[i].p = in.nextInt();
			r[i].a = in.nextInt();
		}

		Arrays.sort(r);

		for (c = 0, i = 0; i < m && n > 0; i++) {
			j = (r[i].a < n) ? r[i].a : n;
			c += j * r[i].p;
			n -= j;
		}

		out.printf("%d\n", c);
		out.close();
	}
}
