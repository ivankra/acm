#include <stdio.h>
#define INF 0x1FFFFFFF

int main()
{
	struct { int n, p; } a[128];
	static char buf[65536];
	static int f[65536];
	int i, j, m, t, x, y;

	for (t = 1; scanf("%d.%d %d", &x, &y, &m) == 3; t++) {
		printf("Case %d:\n", t);

		a[0].n = 1;
		a[0].p = x*100+y;
		m++;

		for (i = 1; i < m; i++) {
			scanf("%d %d.%d", &a[i].n, &x, &y);
			a[i].p = x*100 + y;
		}	

		f[0] = 0;
		for (i = 1; i <= 250; i++) {
			f[i] = INF;
			for (j = 0; j < m; j++) {
				if (a[j].n > i) continue;
				if (f[i-a[j].n] + a[j].p > f[i]) continue;
				f[i] = f[i-a[j].n] + a[j].p;
			}	
		}

		gets(buf);
		gets(buf);

		int p, q, k, r;
		for (p = 0; sscanf(buf+p, " %d%n", &k, &q) >= 1; p += q) {
			for (r = INF, i = k; i <= 250; i++)
				if (f[i] < r) r = f[i];
			printf("Buy %d for $%d.%.2d\n", k, r/100, r%100);
		}	
	}

	return 0;
}
