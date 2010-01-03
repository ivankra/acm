#include <cstdio>

int main() {
char *ans[100][100];
ans[1][1] = "1";
ans[1][2] = "No solution";
ans[1][3] = "No solution";
ans[1][4] = "No solution";
ans[1][5] = "No solution";
ans[1][6] = "No solution";
ans[1][7] = "No solution";
ans[1][8] = "No solution";
ans[1][9] = "No solution";
ans[2][1] = "2";
ans[2][2] = "105263157894736842";
ans[2][3] = "No solution";
ans[2][4] = "No solution";
ans[2][5] = "No solution";
ans[2][6] = "No solution";
ans[2][7] = "No solution";
ans[2][8] = "No solution";
ans[2][9] = "No solution";
ans[3][1] = "3";
ans[3][2] = "157894736842105263";
ans[3][3] = "1034482758620689655172413793";
ans[3][4] = "No solution";
ans[3][5] = "No solution";
ans[3][6] = "No solution";
ans[3][7] = "No solution";
ans[3][8] = "No solution";
ans[3][9] = "No solution";
ans[4][1] = "4";
ans[4][2] = "210526315789473684";
ans[4][3] = "1379310344827586206896551724";
ans[4][4] = "102564";
ans[4][5] = "No solution";
ans[4][6] = "No solution";
ans[4][7] = "No solution";
ans[4][8] = "No solution";
ans[4][9] = "No solution";
ans[5][1] = "5";
ans[5][2] = "263157894736842105";
ans[5][3] = "1724137931034482758620689655";
ans[5][4] = "128205";
ans[5][5] = "102040816326530612244897959183673469387755";
ans[5][6] = "No solution";
ans[5][7] = "No solution";
ans[5][8] = "No solution";
ans[5][9] = "No solution";
ans[6][1] = "6";
ans[6][2] = "315789473684210526";
ans[6][3] = "2068965517241379310344827586";
ans[6][4] = "153846";
ans[6][5] = "122448979591836734693877551020408163265306";
ans[6][6] = "1016949152542372881355932203389830508474576271186440677966";
ans[6][7] = "No solution";
ans[6][8] = "No solution";
ans[6][9] = "No solution";
ans[7][1] = "7";
ans[7][2] = "368421052631578947";
ans[7][3] = "2413793103448275862068965517";
ans[7][4] = "179487";
ans[7][5] = "142857";
ans[7][6] = "1186440677966101694915254237288135593220338983050847457627";
ans[7][7] = "1014492753623188405797";
ans[7][8] = "No solution";
ans[7][9] = "No solution";
ans[8][1] = "8";
ans[8][2] = "421052631578947368";
ans[8][3] = "2758620689655172413793103448";
ans[8][4] = "205128";
ans[8][5] = "163265306122448979591836734693877551020408";
ans[8][6] = "1355932203389830508474576271186440677966101694915254237288";
ans[8][7] = "1159420289855072463768";
ans[8][8] = "1012658227848";
ans[8][9] = "No solution";
ans[9][1] = "9";
ans[9][2] = "473684210526315789";
ans[9][3] = "3103448275862068965517241379";
ans[9][4] = "230769";
ans[9][5] = "183673469387755102040816326530612244897959";
ans[9][6] = "1525423728813559322033898305084745762711864406779661016949";
ans[9][7] = "1304347826086956521739";
ans[9][8] = "1139240506329";
ans[9][9] = "10112359550561797752808988764044943820224719";

int X, K;
scanf("%d %d", &X, &K);
printf("%s\n", ans[X][K]);

}

/*
import java.math.*;
import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) {
		for (int X = 1; X <= 9; X++) {
			for (int K = 1; K <= 9; K++) {
				solve(X, K);
			}
		}		
	}

	static void solve(int X, int K) {
		System.out.printf("ans[%d][%d] = ", X, K);

		BigInteger best = null;

		BigInteger[] ten = new BigInteger[1010];
		ten[0] = BigInteger.ONE;
		for (int n = 1; n <= 1000; n++) ten[n] = ten[n-1].multiply(BigInteger.TEN);

		for (int m = 0; m <= 500; m++) {
			BigInteger z = ten[m].subtract(BigInteger.valueOf(K)).multiply(BigInteger.valueOf(X));
			if (!z.remainder(BigInteger.valueOf(10*K-1)).equals(BigInteger.ZERO))
				continue;
			z = z.divide(BigInteger.valueOf(10*K-1));

			if (z.compareTo(BigInteger.ZERO) < 0) continue;
			if (z.compareTo(ten[m]) >= 0) continue;

			String s1 = z.toString() + String.format("%d", X);
			String s2 = String.format("%d", X) + z.toString();
			BigInteger w = new BigInteger(s1).multiply(BigInteger.valueOf(K));
			if (!w.equals(new BigInteger(s2))) continue;

			BigInteger num = z.multiply(BigInteger.TEN).add(BigInteger.valueOf(X));
			if (best == null || best.compareTo(num) > 0)
				best = num;
		}

		if (best == null) {
			System.out.printf("\"No solution\";\n");
		} else {
			System.out.printf("\"%s\";\n", best);
		}

	}
}

*/