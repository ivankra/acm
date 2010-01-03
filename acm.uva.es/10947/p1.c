#include <stdio.h>
#include <string.h>
#include <math.h>

int px[128], py[128], pr[128], n;
int c[128][128];

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
	int i, j, k, m;
	double d, s;

	while (scanf("%d %d", &k, &m) == 2) {
		for (i = 0; i < 2; i++)
			scanf("%d %d %d", &px[i], &py[i], &pr[i]);
		scanf("%d", &n); n += 2;
		for (i = 2; i < n; i++)
			scanf("%d %d %d", &px[i], &py[i], &pr[i]);

		s = k * m;

		for (i = 0; i < n; i++) {
			c[i][i] = 1;
			for (j = i + 1; j < n; j++) {
				d = sqrt((px[i]-px[j])*(px[i]-px[j]) + (py[i]-py[j])*(py[i]-py[j]));
				d = d - pr[i] - pr[j];
				c[i][j] = c[j][i] = (d < (s+1e-9)) ? 1 : 0;
			}
		}

/*for(i=0;i<n;i++){for(j=0;j<n;j++)putchar(c[i][j]+'0');putchar('\n');}*/

		printf(sol() ? "Larry and Ryan will escape!\n" : "Larry and Ryan will be eaten to death.\n");
	}

	return 0;
}
