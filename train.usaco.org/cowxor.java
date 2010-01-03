/*
ID: infnty1
TASK: cowxor
LANG: JAVA
*/
import java.util.*;
import java.io.*;

public class cowxor {
	public static void main(String[] args) throws IOException {
		BufferedReader input = new BufferedReader(new FileReader("cowxor.in"));
		int N = Integer.parseInt(input.readLine());
		int[] x = new int[N+1];
		int[] bitmap = new int[600000];

		for (int i = 1; i <= N; i++) {
			int a = Integer.parseInt(input.readLine());
			x[i] = x[i-1] ^ a;
		}

		for (int i = 0; i <= N; i++) {
			for (int m = 1; m <= 21; m++) {
				int key = (x[i] >> (21 - m)) | (1 << m);
				bitmap[key >> 5] |= 1 << (key & 31);
			}
		}

		int best = 0;
		for (int t = 1; t <= N; t++) {
			int z = 0;
			for (int m = 1; m <= 21; m++) {
				int z1 = z | (1 << (21-m));
				int key = ((x[t]^z1)>>(21-m)) | (1<<m);
				if (((bitmap[key >> 5] >> (key & 31)) & 1) == 1) {
					z = z1;
				}
			}
			if (z > best) best = z;
		}

		int bestT = 0;
		bitmap = new int[600000];
		bitmap[0] |= 1;
		for (int t = 1; t <= N; t++) {
			int k = x[t] ^ best;
			bitmap[x[t] >> 5] |= 1 << (x[t] & 31);
			if (((bitmap[k >> 5] >> (k & 31)) & 1) == 1) {
				bestT = t;
				break;
			}
		}

                int bestS = 0;
		for (bestS = bestT; bestS > 1; bestS--)
			if ((x[bestS-1] ^ x[bestT]) == best) break;

		PrintWriter out = new PrintWriter("cowxor.out");
		out.printf("%d %d %d\n", best, bestS, bestT);
		out.close();

		System.exit(0);
	}
}
