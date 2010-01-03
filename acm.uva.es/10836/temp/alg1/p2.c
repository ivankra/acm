#include <stdio.h>
#include <math.h>

int main()
{
	static double logf[512], logc[512], logbest;
	static int n, c[4], p[4], guess[4], best[4];
	register double u;
	register int i, j;

	for (logf[0] = 0., i = 1; i < 350; i++)
		logf[i] = logf[i - 1] + log((double)i);

	while (scanf("%d %d %d %d %d", &n, &c[0], &c[1], &c[2], &c[3]) == 5) {
		if ((n | c[0] | c[1] | c[2] | c[3]) == 0)
			break;

		for (i = 0; i < 4; i++)
			logc[i] = log((double)c[i]);

		for (i = 0, j = 0; i < 4; i++)
			j += c[i];

		for (i = 0; i < 4; i++)
			guess[i] = (c[i] * n + (j >> 1)) / j;

printf("{");
for (i = 0; i < 4; i++) printf(" %d",guess[i]);
printf(" } ");


		for (logbest = -1, p[0] = n; p[0] >= 0; p[0]--) {
			for (p[1] = n - p[0]; p[1] >= 0; p[1]--) {
				for (p[2] = n - p[0] - p[1]; p[2]>=0; p[2]--) {
					p[3] = n - p[0] - p[1] - p[2];

					for (u = logf[n], i = 0; i < 4; i++)
						u += p[i]*logc[i] - logf[p[i]];

					if (u < logbest)
						continue;

					logbest = u;
					for (i = 0; i < 4; i++)
						best[i] = p[i];
				}
			}
		}

		printf("[%.10f] ", logbest);
		for (i = 0; i < 4; i++)
			printf(" %c=%d", 'i'+i, best[i]);
		printf("\n");
	}

	return 0;
}
