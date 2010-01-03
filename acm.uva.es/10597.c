#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int vc[256], tc[256], nv, nt, st;
int rt[256], rv[32][32];

int mix(int s, int t)
{
	int r, i, j;

	for (r = 0, i = 0; s; i++, s >>= 1)
		if (s & 1)
			for (j = 0; (t >> j); j++)
				if ((t >> j) & 1) r |= rv[i][j];

	return r;
}

int solve(char *s)
{
	static int a[64][64], n;
	int i, j, k, p, q;

	for (n = 0; *s; s++, n++) {
		if (tc[*s] < 0) return 0;
		a[1][n] = rt[*s];
	}

	for (k = 2; k <= n; k++)
		for (i = 0; (i + k) <= n; i++)
			for (a[k][i] = 0, j = 1; j < k; j++)
				a[k][i] |= mix(a[k - j][i], a[j][i + k - j]);

	return (a[n][0] >> st) & 1;
}

int main()
{
	static char s[65536];
	char *p;
	int i, j;

	while (gets(s) != NULL) {
		for (i = 0; s[i] && !isupper(s[i]); i++);
		if (s[i] == '\0') continue;

		st = s[i];

		for (i = 0; i < 256; i++) vc[i] = tc[i] = -1;

		gets(s);
		for (nv = 0, p = s; *p; p++)
			if (isupper(*p)) vc[*p] = nv++;

		gets(s);
		for (nt = 0, p = s; *p; p++)
			if (*p != '#' && !isspace(*p)) tc[*p] = nt++;

		assert(vc[st] >= 0);
		assert(nv > 0);

		st = vc[st];

		memset(rt, 0, sizeof(rt));
		memset(rv, 0, sizeof(rv));

		while (gets(s) != NULL) {
			for (p = s; *p && *p != '#' && vc[*p] < 0; p++);
			assert(*p != '\0');
			if (*p == '#') break;

			i = vc[*p++];

			while (*p && *p != '>') p++;
			assert(*p == '>');
			p++;

			while (*p && vc[*p] < 0 && tc[*p] < 0) p++;
			assert(*p != '\0');

			if (tc[*p] >= 0) {
				rt[*p] |= (1 << i);
			} else {
				j = vc[*p++];
				while (*p && vc[*p] < 0) p++;
				assert(*p != '\0');
				rv[j][vc[*p]] |= (1 << i);
			}
		}

		while (gets(s) && s[0] != '#')
			printf("%s is%s in L(G)\n", s, solve(s) ? "" : " not");

		printf("\n");
	}

	return 0;
}
