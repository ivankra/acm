#include <stdio.h>

int adj[1024], list[65536], next[65536], last, n;
int red_c[1024], red_d[1024], white_c[1024], white_d[1024];

int white(int, int, int *);

int red(int v, int parent, int *d)
{
	int i, c, c1, d1, c2, d2;

	if (red_c[v] >= 0) {
		*d = red_d[v];
		return red_c[v];
	}

	for (c = 1, *d = 0, i = adj[v]; i != 0; i = next[i]) {
		if (list[i] == parent)
			continue;

		c1 = red(list[i], v, &d1); d1++;
		c2 = white(list[i], v, &d2);

		if (c1 < c2) {
			c += c1;
			(*d) += d1;
		} else if (c1 == c2) {
			c += c1;
			(*d) += ((d1 > d2) ? d1 : d2);
		} else {
			c += c2;
			(*d) += d2;
		}
	}

	red_d[v] = *d;
	return (red_c[v] = c);
}

int white(int v, int parent, int *d)
{
	int i, c, c1, d1;

	if (white_c[v] >= 0) {
		*d = white_d[v];
		return white_c[v];
	}

	for (c = 0, *d = 0, i = adj[v]; i != 0; i = next[i]) {
		if (list[i] == parent)
			continue;

		c += red(list[i], v, &d1);
		*d += d1;
	}

	c1 = red(v, parent, &d1);
	if (c1 < c) {
		c = c1;
		*d = d1;
	} else if (c1 == c && d1 > (*d)) {
		*d = d1;
	}

	white_d[v] = *d;
	return (white_c[v] = c);
}

void add(int u, int v)
{
	int a;

	for (a = adj[u]; a != 0; a = next[a])
		if (list[a] == v) return;

	list[++last] = v;
	next[last] = adj[u];
	adj[u] = last;
}

int main()
{
	int i, k1, k2, m, t, x, y;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		for (last = 0, i = 0; i < n; i++) {
			adj[i] = 0;
			red_c[i] = white_c[i] = -1;
		}

		for (i = 0; i < m && scanf("%d %d", &x, &y) == 2; i++) {
			add(x, y);
			add(y, x);
		}

		for (k1 = 0, k2 = 0, i = 0; i < n; i++) {
			if (red_c[i] < 0 && white_c[i] < 0) {
				k1 += white(i, -1, &x);
				k2 += x;
			}
		}

		printf("%d %d %d\n", k1, k2, m - k2);
	}

	return 0;
}
