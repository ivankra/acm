#include <stdio.h>
#include <string.h>

typedef long long num;

num px[128], py[128], pr[128];
int c[128][128], n;

int sol()
{
	int v[128], s[128], i, x, t;

	memset(v, 0, sizeof(v));

	s[0] = 0;
	v[0] = 1;

	for (t = 1; v[1] == 0 && t-- > 0;) {
		x = s[t];
		for (i = 0; i < n; i++)
			if (c[x][i] && v[i] == 0) { s[t++] = i; v[i] = 1; }
	}

	return v[1];
}

int main()
{
	int i, j;
	num k, m, s;

	while (scanf("%lld %lld", &k, &m) == 2) {
		for (i = 0; i < 2; i++)
			scanf("%lld %lld %lld", &px[i], &py[i], &pr[i]);
		scanf("%d", &n); n += 2;
		for (i = 2; i < n; i++)
			scanf("%lld %lld %lld", &px[i], &py[i], &pr[i]);

		s = k * m;

		for (i = 0; i < n; i++) {
			c[i][i] = 1;
			for (j = i + 1; j < n; j++) {
				num dx=px[i]-px[j], dy=py[i]-py[j], d, w;

				d = dx * dx + dy * dy;
				w = s + pr[i] + pr[j];
				w *= w;

				c[i][j] = c[j][i] = (d <= w);
			}
		}

		printf(sol() ? "Larry and Ryan will escape!\n" : "Larry and Ryan will be eaten to death.\n");
	}

	return 0;
}
