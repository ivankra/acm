#include <stdio.h>
#include <string.h>

#define MAXN	1024

double x[MAXN], y[MAXN], z;
int n;

int solve()
{
	static int d[MAXN], q[MAXN];
	int i, j, h, t;

	memset(d, 0, sizeof(d));
	for (z += 1e-9, d[q[h = 0] = 0] = 1, t = 1; h < t && d[1] == 0; h++)
		for (j = q[h], i = 0; i < n; i++)
			if (d[i] == 0 &&
			    ((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])) < z)
				d[q[t++] = i] = d[j] + 1;

	return (d[1] - 2);
}

int main()
{
	char s[1024];
	int i, v, m;

	for (;;) {
		for (v = 0; gets(s) && sscanf(s, "%d %d", &v, &m) != 2;);
		if (v == 0) break;

		z = (double)v * (double)(60 * m);
		z *= z;

		for (n = 0; gets(s);)
			if (sscanf(s, "%lf %lf", &x[n], &y[n]) == 2)
				n++;
			else if (n >= 2)
				break;

		i = solve();
		if (i < 0)
			printf("No.\n");
		else
			printf("Yes, visiting %d other holes.\n", i);
	}

	return 0;
}
