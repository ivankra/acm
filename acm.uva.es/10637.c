#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_S 128
#define MAX_T 32

static char coprime_tab[MAX_S * MAX_S];
#define IS_COPRIME(x, y) coprime_tab[((x) << 7) + (y)]

static int partition[MAX_T];
static int s, t;

static int gcd(int a, int b)
{
	register int t;
	if (a > b) { t = a; a = b; b = t; }
	while (b != 0) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

static void make_coprimes(void)
{
	int i, j;

	memset(coprime_tab, 0, sizeof(coprime_tab));
	for (i = 1; i < MAX_S; i++)
		for (j = 1; j < MAX_S; j++)
			coprime_tab[i * MAX_S + j] = (gcd(i, j) == 1) ? 1 : 0;
}

static void part(int num, int pos)
{
	int i, j;

	if (pos == t) {
		if (num != 0)
			return;

		for (i = 0; i < t; i++)
			printf(i ? " %d" : "%d", partition[i]);

		printf("\n");
		return;
	}

	for (i = (pos ? partition[pos - 1] : 1); i <= num; i++) {
		for (j = 0; j < pos; j++)
			if (!IS_COPRIME(i, partition[j])) break;

		if (j < pos)
			continue;

		partition[pos] = i;
		part(num - i, pos + 1);
	}
}

int main(void)
{
	int i, n;

	make_coprimes();

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		if (scanf("%d %d", &s, &t) < 2)
			break;
		printf("Case %d:\n", i + 1);
		part(s, 0);
	}

	return 0;
}
