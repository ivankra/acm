/*
ID: infnty1
PROB: barn1
LANG: JAVA
*/
import java.util.*;
import java.io.*;

class barn1 {
	public static void main(String[] args) throws Exception {
		Scanner in = new Scanner(new FileReader("barn1.in"));
		PrintWriter out = new PrintWriter(new FileWriter("barn1.out"));
		boolean[] a;
		int[] b;
		int i, j, s, m, n, c;

		m = in.nextInt();
		s = in.nextInt();
		c = in.nextInt();

		a = new boolean[s+10];
		b = new int[s+10];

		for (i = 0; i <= s; i++)
			a[i] = false;

		while (c-- > 0)
			a[in.nextInt()] = true;

		for (i = 0; !a[i]; i++);

		for (n = 0;;) {
			while (i <= s && a[i]) i++;
			for (j = 0; i <= s && !a[i]; i++, j++);
			if (i > s) break;
			b[n++] = j;
		}

		for (i = 1; i < n; i++) {
			c = b[i];
			for (j = i - 1; j >= 0 && b[j] < c; j--)
				b[j+1] = b[j];
			b[j+1] = c;
		}

		for (i = 1; !a[i]; i++);
		for (j = s; !a[j]; j--);
		c = j - i + 1;
		for (i = 0; i < n && i < (m - 1); i++) c -= b[i];

		out.printf("%d\n", c);
		out.close();
		System.exit(0);
	}
}
