#include <stdio.h>
#include <string.h>

#define INF	0x3FFFFFFF
#define MAXN	10240
#define MAXL	42

static int wordlen[MAXN], cumlen[MAXN], width, nwords;
static int gaplen[MAXL*MAXN], gapnext[MAXL*MAXN], gapfree;
static char *word[MAXN], spaces[1024];

static int gcompare(int g1[], int n1, int p1, int g2[], int n2, int p2)
{
	for (; n1 > 0 && n2 > 0; g1++, g2++, n1--, n2--)
		if (g1[0] != g2[0]) return (g1[0] - g2[0]);

	for (; n1 > 0; g1++, n1--, p2 = gapnext[p2])
		if (g1[0] != gaplen[p2]) return (g1[0] - gaplen[p2]);

	for (; n2 > 0; g2++, n2--, p1 = gapnext[p1])
		if (gaplen[p1] != g2[0]) return (gaplen[p1] - g2[0]);

	for (; p1 != 0; p1 = gapnext[p1], p2 = gapnext[p2])
		if (gaplen[p1] != gaplen[p2]) return (gaplen[p1] - gaplen[p2]);

	return 0;
}

static int cost(int a, int b, int g[])
{
	int i, k, m, s;

	if (a == b)
		return (wordlen[a] < width) ? 500 : 0;

	s = cumlen[b + 1] - cumlen[a];
	if ((s + b - a) > width)
		return INF;

	s = width - s;
	k = b - a;

	m = s / k;
	for (i = 0; i < k; i++)
		g[i] = m;

	m = s - k * m;
	for (i = k - 1; i >= 0 && m > 0; i--, m--)
		g[i]++;

	for (m = 0, i = 0; i < k; i++)
		m += (g[i] - 1) * (g[i] - 1);

	return m;
}

static void fmt()
{
	static int bad[MAXN], succ[MAXN], gptr[MAXN];
	static int g1[MAXL], g2[MAXL];
	int i, k, a, b;

	gapfree = 1;

	bad[nwords] = 0;
	gptr[nwords] = 0;

	for (a = nwords - 1; a >= 0; a--) {
		bad[a] = INF;
		succ[a] = nwords;

		for (b = a; b < nwords; b++) {
			k = cost(a, b, g2);
			if (k == INF) break;

			k += bad[b + 1];
			if (k > bad[a])
				continue;

			if (k == bad[a]) {
				if (gcompare(g1, succ[a] - a - 1, gptr[succ[a]],
					     g2, b - a, gptr[b]) < 0)
					continue;
			}

			bad[a] = k;
			succ[a] = b + 1;
			memcpy(g1, g2, MAXL * sizeof(int));
		}

		gptr[a] = gptr[succ[a]];
		for (k = succ[a] - a - 2; k >= 0; k--) {
			gapnext[gapfree] = gptr[a];
			gaplen[gapfree] = g1[k];
			gptr[a] = gapfree++;
		}
	}

	for (i = 0, a = gptr[0]; i < nwords;) {
		for (k = succ[i]; i < k;) {
			printf("%s", word[i]);
			if (++i < k) {
				fwrite(spaces, 1, gaplen[a], stdout);
				a = gapnext[a];
			}
		}
		printf("\n");
	}

	printf("\n");
}

int main()
{
	static int wtab[256], wtabz[256];
	static char wordbuf[65536], buf[16384];
	char *p, *q;
	int i;

	for (i = 0; i < 256; i++)
		wtabz[i] = wtab[i] = (i >= 33 && i <= 126);
	wtabz[0] = 1;

	memset(spaces, ' ', sizeof(spaces));

	while (gets(buf)) {
		if (sscanf(buf, "%d", &width) != 1)
			continue;

		if (width == 0)
			break;

		for (nwords = 0, word[0] = wordbuf; gets(buf);) {
			for (p = buf; *p; p++);
			for (p--; p >= buf && wtab[(int)*p] == 0; p--);

			*++p = '\0';
			if (p == buf)
				break;

			for (p = buf;;) {
				while (!wtabz[(int)*p]) p++;

				if (*p == '\0')
					break;

				for (q = word[nwords]; wtab[(int)*p];)
					*q++ = *p++;
				*q = '\0';
				wordlen[nwords] = q - word[nwords];

				word[++nwords] = q + 1;
			}
		}

		for (cumlen[0] = 0, i = 0; i < nwords; i++)
			cumlen[i + 1] = cumlen[i] + wordlen[i];

		fmt();
	}

	return 0;
}
