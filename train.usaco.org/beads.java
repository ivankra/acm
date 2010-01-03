/*
ID: infnty1
PROB: beads
LANG: JAVA
*/
import java.io.*;
import java.util.*;
import java.util.regex.*;

class beads {
	static int solve(int n, String s) {
		int p, r, c, k, x;
		if (n <= 0) return 0;

		for (p = r = 0; p < n; p++) {
			for (c = k = 0, x = p; k < n; k++, x = (x + 1) % n) {
				if (s.charAt(x) == 'w')
					continue;
				else if (c == 0)
					c = s.charAt(x);
				else if (c != s.charAt(x))
					break;
			}

			x = (p + n - 1) % n;
			for (c = 0; k < n; x = (x + n - 1) % n, k++) {
				if (s.charAt(x) == 'w')
					continue;
				else if (c == 0)
					c = s.charAt(x);
				else if (c != s.charAt(x))
					break;
			}

			if (k > r) r = k;			
		}

		return r;
	}

	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(new FileReader("beads.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("beads.out")));
		int n;
		String s;

		n = sc.nextInt();
		s = sc.next("[rbw]*");
		
		out.printf("%d\n", solve(n, s));
		out.close();

		System.exit(0);
	}	
}
