#include <stdio.h>

/*

     total[k][i] - total DI to cover topics i..n in k lectures

     cov[i] = number of conseq topics (starting from i) that can be covered
              in a lecture, were it to start from topic i
	      at least 1, at most 'len'.

     di[x] =  0         x == 0,
              -C        1 <= x <= 10
              (x-10)^2  x > 10

     total[k][i] = min(
         total[k-1][i+1] + di[len - t[i]],
	 total[k-1][i+2] + di[len - t[i] - t[i+1]],
	 ...
          1 <= Z <= cov[i]:
          total[k-1][i+Z] + di[len - (cum[i + Z - 1] - cum[i - 1])]
         ...
	 total[k-1][i+cov[i]] + di[len - t[i] - t[i+1] - ... - t[i+cov[i]]]
       )

     total[0][n] = 0
     total[0][i] = +INF (i < n)

     final answer: total[m][1]
*/

#define INF 0x3FFFFFFF

static int t[1024], cum[1024], cov[1024], di[1024], m, n, len, c;
static int total1[1024], total2[1024];

int main()
{
	int i, j, k, r, s, *total, *next;

	for (di[0] = 0, i = 1; i < 1000; i++)
		di[10 + i] = i * i;

	for (s = 1; scanf("%d %d %d", &n, &len, &c) == 3 && n > 0; s++) {
		for (i = 1; i <= n; i++)
			scanf("%d", &t[i]);

		for (i = 1; i <= 10; i++)
			di[i] = -c;

		for (cum[0] = 0, i = 1; i <= n; i++)
			cum[i] = cum[i - 1] + t[i];

		for (i = 1; i <= n; i++) {
			for (j = i; j <= n; j++)
				if ((cum[j] - cum[i - 1]) > len) break;
			cov[i] = j - i;
		}

		for (i = 1, m = 0; i <= n; i += cov[i], m++);

		total = total1;
		next = total2;

		for (i = 0; i <= n; i++)
			total[i] = INF;
		total[n + 1] = 0;

		for (k = 1; k <= m; k++) {
			for (i = 1; i <= n; i++) {
				next[i] = INF;
				for (j = 1; j <= cov[i]; j++) {
					r = di[len - cum[i+j-1] + cum[i-1]] +
					    total[i + j];

					if (r < next[i])
						next[i] = r;
				}
			}

			total = next;
			next = (next == total1) ? total2 : total1;
		}

		printf("%sCase %d:\n", (s == 1) ? "" : "\n", s);
		printf("Minimum number of lectures: %d\n", m);
printf("DI=%d\n",total[1]);

	}

	return 0;
}
