#include <stdio.h>
#include <string.h>
#include <ctype.h>

int adj[32][32], use[32], list[32], n;

void parse(char *s)
{
	int i, k, x;

	memset(adj, 0, sizeof(adj));
	memset(use, 0, sizeof(use));

	for (;;) {
		while (*s && !isalpha(*s)) s++;
		if (*s == '\0') break;

		x = toupper(*s) - 'A';
		use[x] = 1;

		for (s++; *s && *s != ';'; s++) {
			if (isalpha(*s)) {
				use[k = toupper(*s) - 'A'] = 1;
				adj[x][k] = adj[k][x] = 1;
			}
		}
	}

	for (i = n = 0; i < 26; i++)
		if (use[i]) list[n++] = i;
}

int eval(int p[])
{
	int i, j, r;

	for (r = 0, i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (adj[list[p[i]]][list[p[j]]] && (j - i) > r)
				r = j - i;

	return r;
}

void solve()
{
	static int p[128], best[128], best_r;
	int i, j, k;

	best_r = 0x7FFFFFFF;

	for (i = 0; i < n; i++)
		best[i] = p[i] = i;

	for (;;) {
		if ((i = eval(p)) < best_r) {
			best_r = i;
			for (i = 0; i < n; i++) best[i] = p[i];
		}

		for (i = n - 2; i >= 0 && p[i] > p[i + 1]; i--);
		if (i < 0) break;

		for (j = n - 1; p[j] < p[i]; j--);

		k = p[i];
		p[i] = p[j];
		p[j] = k;

		for (i++, j = n - 1; i < j;) {
			k = p[i];
			p[i++] = p[j];
			p[j--] = k;
		}
	}

	for (i = 0; i < n; i++)
		printf("%c ", list[best[i]] + 'A');

	printf("-> %d\n", best_r);
}

int main()
{
	static char buf[65536];

	while (gets(buf) && strchr(buf, '#') == NULL) {
		parse(buf);
		solve();
	}

	return 0;
}
