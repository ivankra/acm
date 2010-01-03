#include <stdio.h>
#include <string.h>

int h[256], d[256], w[256], v[256], o[256], n, z;
unsigned char f[201][201][101];

int _in(int a, int b)
{
	return h[a] <= (h[b]-2*w[b]) && d[a] <= (d[b]-2*w[b]);
}

int in(int a, int b)
{
	return ((a | b) == 0) ? (a == 0 && b > 0) : _in(o[a], o[b]);
}

void dfs(int x)
{
	int y;
	for (v[x] = 1, y = 1; y <= n; y++)
		if (v[y] == 0 && _in(y,x)) dfs(y);
	o[z++] = x;
}

int main()
{
	int i, j, k, m, t;

	for (t = 0; scanf("%d", &n) == 1 && n > 0;) {
		if (t >= 254) {
			t = 1;
			memset(f, 0, sizeof(f));
		}

		if (t++) printf("\n");

		for (n *= 2, i = 1; i <= n; i++)
			scanf("%d %d %d", &h[i], &d[i], &w[i]);

		memset(v, 0, sizeof(v));
		for (i = z = 1; i <= n; i++)
			if (v[i] == 0) dfs(i);

		f[1][0][1] = t;
		m = n/2;

		for (i = 2; i <= n; i++) {
			if (in(i-1, i))
				for (j = 0; j < i; j++)
					for (k = 1; k <= i && k <= m; k++)
						f[i][j][k] = f[i-1][j][k-1];

			for (k = 1; k <= i && k <= m; k++) {
				if (f[i][i-1][k] == t) continue;
				for (j = 0; j < i; j++)
					if (f[i-1][j][i-k] == t && in(j,i)) {
						f[i][i-1][k] = t;
						break;
					}
			}
		}

		for (i = n, j = 1; j < n && f[i][j][m] != t; j++);

		for (k = 0; k <= n; k++) v[k] = -1;

		for (k = n/2, m = 0;;) {
			v[i] = m;
			if (k <= 1) break;

			if (f[i-1][j][k-1] == t && in(i-1, i)) {
				i--; k--;
				continue;
			}

			for (j = 0; j < i; j++)
				if (f[i-1][j][i-k] == t && in(j,i)) break;

			k = i - k;
			i--;
			m ^= 1;
		}

		for (m ^= 1, i = 1; i <= n; i++)
			if (v[i] < 0) v[i] = m;

		for (i = n; i >= 1; i--)
			if (v[i] == 0) printf("%d %d %d\n", h[o[i]], d[o[i]], w[o[i]]);
		printf("-\n");
		for (i = n; i >= 1; i--)
			if (v[i] == 1) printf("%d %d %d\n", h[o[i]], d[o[i]], w[o[i]]);
	}

	return 0;
}
