#include <stdio.h>
#include <stdlib.h>

#define N 16384

int read(int, char *, int);

static int next[N], ref[N], lg[N], last, n, m;
static int E[N], D[N], R[N], depth[N], M[16][N], P[14][N];

static void dfs(int x)
{
	int i;
	depth[x] = depth[P[0][x]] + 1;
	E[m++] = x;
	for (i = next[x]; i != 0; i = next[i])
		if (ref[i] != P[0][x]) P[0][ref[i]] = x, dfs(ref[i]);
	if (depth[x] > 0) E[m++] = P[0][x];
}

static int up(int x, int k)
{
	while (k > 0) {
		x = P[lg[k]][x];
		k -= 1 << lg[k];
	}
	return x;
}

static int lca(int x, int y)
{
	int t;

	x = R[x]; y = R[y];
	if (x > y) t = x, x = y, y = t;

	t = lg[y - x];
	y = M[t][y - (1 << t) + 1];
	return (M[t][x] < y) ? M[t][x] : y;
}

int main()
{
	static char buf[24*1048576];
	static int isdig[256];
	int i, j, a, b, c;
	char *p;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;
	read(0, p = buf, sizeof(buf));
#define R(w) {while(!isdig[*p])p++;for(w=(*p++)-'0';isdig[*p];)w=w*10+(*p++)-'0';p++;}

	for (i = 0; i <= 13; i++) {
		lg[c = 1 << (i + 1)] = i + 1;
		for (j = 1 << i; j < c; j++) lg[j] = i;
	}

	for (;;) {
		R(n); if (n == 0) break;

		for (i = 0; i <= n; i++) next[i] = 0;

		for (i = 1, last = n; i < n; i++) {
			R(a); R(b);
			ref[++last] = b; next[last] = next[a]; next[a] = last;
			ref[++last] = a; next[last] = next[b]; next[b] = last;
		}

		P[0][0] = P[0][1] = m = 0; depth[0] = -1; dfs(1);
		for (i = 1; i <= n; i++) R[i] = -1;
		for (i = 0; i < m; i++) if (R[E[i]] < 0) R[E[i]] = i;
		for (i = 0; i < m; i++) D[i] = depth[E[i]];

		for (c = 0, i = 1; i <= n; i++)
			if (depth[i] > c) c = depth[i];

		for (c++, j = 1; (c >> j) != 0; j++)
			for (i = 1; i <= n; i++)
				P[j][i] = P[j-1][P[j-1][i]];

		for (i = 0; i < m; i++)
			M[0][i] = D[i];

		for (j = 0, a = 1, c = 2; c <= m; j++, a <<= 1, c <<= 1)
			for (i = m - c; i >= 0; i--)
				M[j+1][i] = (M[j][i] < M[j][i+a]) ? M[j][i] : M[j][i+a];

		R(c);
		while (c-- > 0) {
			R(a); R(b);
			if (depth[b] > depth[a])
				i = b, b = a, a = i;

			i = lca(a, b);
			i = depth[a] + depth[b] - 2 * i;

			if ((i & 1) == 0) {
				i >>= 1;
				printf("The fleas meet at %d.\n", up(a, i));
			} else {
				i >>= 1;
				if (depth[a] == depth[b]) {
					a = up(a, i);
					b = up(b, i);
				} else {
					a = up(a, i);
					b = P[0][a];
				}
				if (a > b) i = a, a = b, b = i;
				printf("The fleas jump forever between %d and %d.\n", a, b);
			}
		}
	}

	exit(0);
}
