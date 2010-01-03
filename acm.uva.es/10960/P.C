#include <stdio.h>
#include <string.h>
#include <ctype.h>

int np, ni, nc;
int link[32][16], parent[8192], color[8192], not_color[8192], n;

int find(int x)
{
	int y, t;
	for (y = x; parent[y] != y; y = parent[y]);
	for (; x != y; x = t) {
		t = parent[x];
		parent[x] = y;
	}
	return y;
}

int solve()
{
	static char buf[1024];
	int b[32], i, j, k, x, y, nu, valid;

	valid = 1;

	scanf("%d %d %d %d", &np, &ni, &nc, &nu);

	for (n = 0, i = 0; i < np; i++)
		for (j = 0; j < ni; j++)
			link[i][j] = n++;

	for (i = 0; i < n; i++) {
		parent[i] = i;
		color[i] = -1;
		not_color[i] = 0;
	}

	while (nu-- > 0 && scanf(" %s", buf) >= 1) {
		buf[0] = toupper(buf[0]);
		if (buf[0] == 'S')
			scanf(" %*s %*s %*s %d =", &x);
		else if (buf[0] == 'C')
			scanf(" %d %*s %*s %d =", &y, &x);
		else
			scanf(" %*s %d %*s %*s %d =", &y, &x);

		memset(b, 0, sizeof(b));
		while ((i = getchar()) != EOF && i != '\n')
			if (isalpha(i)) b[toupper(i) - 'A'] = 1;

		if (!valid) continue;

		if (buf[0] == 'C') {
			for (i = 0; i < 26; i++) {
				if (b[i] == 0) continue;
				j = find(link[i][x]);
				if (color[j] >= 0 && color[j] != y) valid = 0;
				if (not_color[j] & (1 << y)) valid = 0;
				color[j] = y;
			}
		} else if (buf[0] == 'S') {
			for (y = 0; y < 26 && b[y] == 0; y++);
			if (y < 26) y = find(link[y][x]);

			for (i = 0; i < 26; i++) {
				if (b[i] == 0) continue;

				j = find(link[i][x]);
				if (y == j) continue;

				if (color[y] >= 0 && color[j] >= 0 &&
				    color[y] != color[j]) {
					valid = 0;
					continue;
				}

				parent[j] = y;

				if (color[j] >= 0) color[y] = color[j];

				not_color[y] |= not_color[j];
				if (color[y] >= 0 && (not_color[y] & (1 << color[y])) != 0) valid = 0;
			}
		} else {
			for (i = 0; i < 26; i++) {
				if (b[i] == 0) continue;
				j = find(link[i][x]);
				not_color[j] |= 1 << y;
				if (color[j] >= 0 && y == color[j]) valid = 0;
			}
		}
	}

	if (!valid) return 1;

	for (i = 0; i < n; i++) {
		j = find(i);
		if (j != i) continue;

		not_color[i] &= (1 << nc) - 1;
		if (color[i] >= 0) {
			if ((not_color[i] & (1 << color[i])) != 0) return 1;
		} else {
			if (not_color[i] == ((1 << nc) - 1)) return 1;
		}
	}

	for (i = 0; i < n; i++) {
		if (parent[i] != i || color[i] >= 0) continue;

		for (k = 0; k < nc; k++)
			if ((not_color[i] & (1 << k)) == 0) break;
		if (k >= nc) return 1;

		for (j = k + 1; j < nc; j++)
			if ((not_color[i] & (1 << j)) == 0) break;
		if (j < nc) continue;

		color[i] = k;
	}

	for (i = 0; i < np; i++) {
		printf("%c", 'A'+i);
		for (j = 0; j < ni; j++) {
			k = color[parent[link[i][j]]];
			if (k >= 0) {
				printf(" %d", k);
			} else {
				printf(" ?");
			}
		}
		printf("\n");
	}

	return 0;
}

int main()
{
	int t;
	for (scanf("%d", &t); t-- > 0;) {
		if (solve()) printf("Contradiction\n");
		if (t) printf("\n");
	}
	return 0;
}
