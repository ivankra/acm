#include <stdio.h>

static int adj[1024], list[65536], next[65536], last, n;
static int red_c[1024], red_d[1024], white_c[1024], white_d[1024];

int read(int, char *, int);

static int white(int, int);

static int red(int v, int parent)
{
	int i, c, d, c1, d1, c2, d2;

	if (red_c[v] >= 0)
		return red_c[v];

	for (c = 1, d = 0, i = adj[v]; i != 0; i = next[i]) {
		if (list[i] == parent)
			continue;

		c1 = red(list[i], v); d1 = red_d[list[i]] + 1;
		c2 = white(list[i], v); d2 = white_d[list[i]];

		if (c1 < c2) {
			c += c1;
			d += d1;
		} else if (c1 == c2) {
			c += c1;
			d += ((d1 > d2) ? d1 : d2);
		} else {
			c += c2;
			d += d2;
		}
	}

	red_d[v] = d;
	return (red_c[v] = c);
}

static int white(int v, int parent)
{
	int i, c, d, c1, d1;

	if (white_c[v] >= 0)
		return white_c[v];

	for (c = 0, d = 0, i = adj[v]; i != 0; i = next[i]) {
		if (list[i] == parent)
			continue;

		c += red(list[i], v);
		d += red_d[list[i]];
	}

	c1 = red(v, parent);
	d1 = red_d[v];
	if (c1 < c) {
		c = c1;
		d = d1;
	} else if (c1 == c && d1 > d) {
		d = d1;
	}

	white_d[v] = d;
	return (white_c[v] = c);
}

static int isdig[256];

int main()
{
	static char inbuf[2*1048576];
	static int k1, k2, t;
	register char *inp;
	int i, m, x, y;

	/*for (i = 0; i < 256; i++) isdig[i] = 0;*/
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

#define READ(var) { \
	while (!isdig[*inp]) inp++; \
	for (var = *inp++ - '0'; isdig[*inp];) var = var * 10 + *inp++ - '0'; \
}

	READ(t);
	while (t-- > 0) {
		READ(n); READ(m);

		for (last = 0, i = 0; i < n; i++) {
			adj[i] = 0;
			red_c[i] = white_c[i] = -1;
		}

		for (i = 0; i < m; i++) {
			READ(x); READ(y);

			list[++last] = x;
			next[last] = adj[y];
			adj[y] = last;

			list[++last] = y;
			next[last] = adj[x];
			adj[x] = last;
		}

		for (k1 = 0, k2 = 0, i = 0; i < n; i++) {
			if (white_c[i] < 0) {
				k1 += white(i, -1);
				k2 += white_d[i];
			}
		}

		printf("%d %d %d\n", k1, k2, m - k2);
	}

	return 0;
}
