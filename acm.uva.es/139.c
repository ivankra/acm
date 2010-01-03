#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct {
	char s[16], name[32];
	int s_len, name_len;
	double c;
} tab[131072];

int ntab;

int find(char *s, int n)
{
	static char t[256];
	int a, b, c, r;

	for (a = 0; a < n; a++)
		t[a] = s[a];
	t[a] = '\0';

	for (a = 0, b = ntab - 1; a <= b;) {
		r = strcmp(tab[c = (a + b) >> 1].s, t);

		if (r < 0)
			a = c + 1;
		else if (r > 0)
			b = c - 1;
		else
			return c;
	}

	return -1;
}

int area(char *s)
{
	int i, j, k, n;

	n = strlen(s);
	if (n < 6 || n > 15 || s[0] != '0')
		return -1;

	for (k = 2; k <= 6; k++) {
		i = find(s, k);
		if (i < 0) continue;

		if (tab[i].s_len < 2) continue;
		if (tab[i].s_len > 6) continue;
		if (tab[i].s[0] != '0') continue;

		j = n - tab[i].s_len;
		if (4 <= j && j <= 7) return i;

		if (tab[i].s_len < 3) continue;
		if (tab[i].s_len > 5) continue;
		if (tab[i].s[1] != '0') continue;

		if (4 <= j && j <= 10) return i;
	}

	return -1;
}

int main()
{
	static char s[65536];
	int i, k, d;

	while (scanf(" %s", tab[ntab].s) == 1) {
		if (strcmp(tab[ntab].s, "000000") == 0)
			break;

		getchar();

		for (i = 0; (k = getchar()) != EOF && k != '$';)
			tab[ntab].name[i++] = k;
		tab[ntab].name[i] = '\0';

		scanf("%lf", &tab[ntab].c);

		tab[ntab].s_len = strlen(tab[ntab].s);
		tab[ntab].name_len = strlen(tab[ntab].name);

		ntab++;
	}

	qsort(tab, ntab, sizeof(tab[0]), strcmp);

	while (scanf(" %s %d", s, &d) == 2 && s[0] != '#') {
		if (s[0] != '0') {
			printf("%-16sLocal%30s%5d  0.00   0.00\n", s, s, d);
			continue;
		}

		i = area(s);

		if (i < 0) {
			printf("%-16s%-35s%5d        -1.00\n", s, "Unknown", d);
			continue;
		}

		printf("%-16s%s%*s%5d%6.2f%7.2f\n",
			s, tab[i].name, 35 - tab[i].name_len,
			s + tab[i].s_len, d,
			tab[i].c / 100., d * tab[i].c / 100.);
	}

	return 0;
}
