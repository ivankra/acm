#include <cstdio>

int p[128]={0}, g[128][128], N, M;

int main()
{
	scanf("%d %d", &N, &M);
	for (int n = 1; n <= N; n++) {
		for (int sum = n-1; sum >= 0; sum--) {
			for (int me = sum; me >= 0; me--) {
				int him = sum - me;
				if (him >= N) continue;

				g[me][him] = 0;
				for (int m = 1; m <= M && me+him+m <= n; m++)
					g[me][him] >?= n - (me+him+m==n ? p[him] : g[him][me+m]);
			}
		}
		p[n] = g[0][0];
	}
	printf("%d\n", p[N]);
}


/*using System;

class ProblemG_kia {
	public int solve(int N, int M) {
		int[] profit = new int[N+1];
		profit[0] = 0;

		int[,] g = new int[N+1, N+1];
		for (int n = 1; n <= N; n++) {
			for (int sum = n-1; sum >= 0; sum--) {
				for (int me = n-1; me >= 0; me--) {
					int him = sum - me;
					if (him < 0 || him >= n) continue;

					g[me, him] = 0;
					for (int m = 1; m <= M && me+him+m <= n; m++) {
						int r;
						if (me+him+m == n)
							r = n - profit[him];
						else
							r = n - g[him, me+m];

						if (r > g[me, him])
							g[me, him] = r;
					}
				}
			}
			profit[n] = g[0, 0];
		}

		return profit[N];
	}

	public static void Main(string[] args) {
		string ln;
		while ((ln = Console.ReadLine()) != null) {
			string[] s = ln.Split(' ');
			int N = int.Parse(s[0]), M = int.Parse(s[1]);
			Console.WriteLine("{0}", new ProblemG().solve(N, M));
		}
	}
}
*/
