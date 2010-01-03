#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXM 524288

int adjp[676], adjn, next[MAXM], ref[MAXM];
int dist[676][676], uf[676];

void solve(int u, int v)
{
	static int p[1024], d[1024], f[1024];
	int i, j, a;

	memset(f, 0, sizeof(f));
	for (i = 0; i < 676; i++) d[i] = 0x7fffffff, p[i] = -1;
	d[p[v] = v] = 0;

	while (p[u] < 0) {
		for (i = 0; f[i]; i++);
		if (i > 676) break;

		for (j = i + 1; j < 676; j++)
			if (f[j] == 0 && d[j] < d[i]) i = j;

		f[i] = 1;

		for (a = adjp[i]; a != 0; a = next[a]) {
			if ((d[i] + dist[i][ref[a]]) >= d[ref[a]]) continue;
			d[ref[a]] = d[i] + dist[i][ref[a]];
			p[ref[a]] = i;
		}
	}

	printf("%3d: %c%c", d[u], (u / 26) + 'A', (u % 26) + 'a');
	for (i = p[u], j = u / 26;; i = p[i]) {
		if ((i / 26) != j) printf("=%c", 'A' + (j = i / 26));
		printf("%c", (i % 26) + 'a');
		if (i == v) break;
	}
	printf("\n");
}

void add(int u, int v, int c)
{
	if (dist[u][v] || u == v) return;

	dist[u][v] = dist[v][u] = c;

	adjn++;
	ref[adjn] = v;
	next[adjn] = adjp[u];
	adjp[u] = adjn;

	adjn++;
	ref[adjn] = u;
	next[adjn] = adjp[v];
	adjp[v] = adjn;
}

int cvt(int a, int b)
{
	return ((a | 0x20) - 'a') * 26 + (b | 0x20) - 'a';
}

int find(int x)
{
	int y, z;

	for (z = x; uf[z] != z; z = uf[z]);

	while (x != z)
		y = uf[x], uf[x] = z, x = y;

	return z;
}

int main()
{
	char s[1024], *p;
	int i, j, k, r, m;

	adjn = 0;
	memset(adjp, 0, sizeof(adjp));
	memset(dist, 0, sizeof(dist));

	for (i = 0; i < 676; i++)
		uf[i] = i;

	while (gets(s) && sscanf(s, "%d", &m) != 1);

	while (m-- > 0 && gets(s)) {
		for (p = s; *p && !isalpha(*p); p++);
		if (*p == '\0') continue;

		for (r = *p++; *p && *p != ':'; p++);
		if (*p == '\0') continue;

		while (*p && !isalpha(*p)) p++;
		if (*p == '\0') continue;

		for (i = *p++;;) {
			while (*p && !isalpha(*p) && *p != '=') p++;
			if (*p == '\0') {
				break;
			} else if (*p == '=') {
				for (p++; !isalpha(*p); p++);
				j = *p++;
				while (!isalpha(*p)) p++;
				k = *p++;
				uf[find(cvt(r, i))] = find(cvt(j, k));
			} else {
				add(cvt(r, i), cvt(r, *p), 1);
				i = *p++;
			}
		}
	}

	for (i = 0; i < 676; i++)
		find(i);

	for (i = 0; i < 676; i++)
		for (j = 0; j < i; j++)
			if (uf[i] == uf[j])
				add(i, j, 3);

	while (gets(s) && s[0] != '#') {
		for (p = s; *p && !isalpha(*p); p++);
		if (*p == '\0') continue;

		for (i = *p++; *p && !isalpha(*p);) p++;
		if (*p == '\0') continue;

		i = cvt(i, *p++);

		while (*p && !isalpha(*p)) p++;
		if (*p == '\0') continue;

		for (j = *p++; *p && !isalpha(*p);) p++;
		if (*p == '\0') continue;

		j = cvt(j, *p++);

		solve(i, j);
	}

	return 0;
}
