#include <stdio.h>
#include <string.h>

int total[8], total1[8], got[65536], testno;
double prob[16][8], tab[65536];

double f(int n, int x[])
{
	int i, j;

	if (n == 0)
		return 1.;

	for (j = 0, i = 0; i < 5; i++)
		j = j * total1[i] + x[i];

	if (got[j] == testno)
		return tab[j];

	for (got[j] = testno, tab[j] = 0, i = 0; i < 5; i++)
		if (x[i] > 0) {
			x[i]--;
			tab[j] += prob[n-1][i] * f(n - 1, x);
			x[i]++;
		}

	return tab[j];
}

int main()
{
	static int x[8], y[8], n, t;
	static double p[8], q;
	int i, j;

	/*memset(got, 0, sizeof(got));*/
	testno = 1;

	for (scanf("%d", &t); t-- && scanf("%d", &n) == 1; testno++) {
		for (i = 0; i < 5; i++)
			scanf("%d", &total[i]);

		for (i = n; i--;)
			for (j = 0; j < 5; j++)
				scanf("%lf", &prob[i][j]);

		for (i = 0; i < 5; i++) {
			x[i] = total[i];
			total1[i] = total[i] + 1;
		}

		q = f(n, x);
		for (i = 0; i < 5; i++) {
			if (total[i] == 0) {
				p[i] = -1;
				continue;
			}

			for (j = 0; j < 5; j++)
				y[j] = total[j];
			y[i]--;

			p[i] = prob[n-1][i] * f(n - 1, y) / (q * total[i]);
		}

		for (i = 0, j = 1; j < 5; j++)
			if (p[j] > (p[i] + 1e-9)) i = j;

		printf("%d %.3f\n", i + 1, p[i]);
	}

	return 0;
}
