/*
ID: infnty1
PROB: money
LANG: JAVA
*/
import java.io.*;
import java.util.*;

class money {
	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(new FileReader("money.in"));
		PrintWriter out = new PrintWriter(new FileWriter("money.out"));

		int V = sc.nextInt();
		int N = sc.nextInt();
		long[] a = new long[N+1];

		for (int i = 0; i <= N; i++) a[i] = 0;
		a[0] = 1;

		for (int i = 0; i < V; i++) {
			int j, k, C = sc.nextInt();
			for (j = C, k = 0; j <= N;) a[j++] += a[k++];
		}
		
		out.println(a[N]);
		out.close();
		System.exit(0);
	}
}
