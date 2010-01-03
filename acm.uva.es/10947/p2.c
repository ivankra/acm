#include <stdio.h>
#include <string.h>

typedef long long num;

num px[128], py[128], pr[128];
int c[128][128], n;

num isqrt(num a)
{
	num x, y;

	for (x = a; x > 1; x = y) {
		y = (x + (a / x)) >> 1;
		if (y >= x) break;
	}

	return x;
}

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

		s = k * m * k * m;

		for (i = 0; i < n; i++) {
			c[i][i] = 1;
			for (j = i + 1; j < n; j++) {

num dx=px[i]-px[j], dy=py[i]-py[j], d, r;

d = dx * dx + dy * dy;
r = pr[i] + pr[j];
r *= r;

/* (d + r - s)^2 <= 4 d r */
				c[i][j] = c[j][i] = 0;
				if ((d + r - s) < 0)
					c[i][j] = c[j][i] = 1;
				else if (((d+r-s)*(d+r-s)) <= (4*d*r))
					c[i][j] = c[j][i] = 1;
			}
		}

/*for(i=0;i<n;i++){for(j=0;j<n;j++)putchar(c[i][j]+'0');putchar('\n');}*/

		printf(sol() ? "Larry and Ryan will escape!\n" : "Larry and Ryan will be eaten to death.\n");
	}

	return 0;
}
