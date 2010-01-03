#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct {
	int zip, defined, cycle, m;
	int a[128];
} def[32];

int findcyc(int d)
{
	static int a[32];
	int x, n;

	if (!def[d].defined || def[d].zip)
		return 0;

	memset(a, 0, sizeof(a));
	for (x = d, n = 0; def[x].defined && !def[x].zip && a[x] == 0;) {
		a[x] = 1;
		n += def[x].m;
		x = def[x].a[def[x].m];
	}

	return ((x == d) ? n : 0);
}

int eval(int d, int n)
{
	for (;;) {
		if (def[d].zip) {
			d = def[d].a[n & 1];
			n >>= 1;
			continue;
		}

		if (def[d].cycle > 0)
			n %= def[d].cycle;

		if (n < def[d].m)
			return def[d].a[n];

		n -= def[d].m;
		d = def[d].a[def[d].m];
	}
}

int main()
{
	static char s1[1024], s2[1024];
	int i, n, m, t, x, y;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &n, &m) == 2;) {
		memset(def, 0, sizeof(def));

		while (n-- > 0 && scanf(" %s =", s1) == 1) {
			x = toupper(s1[0]) - 'A';

			def[x].defined = 1;

			scanf(" %s", s1);
			if (strcmp(s1, "zip") == 0) {
				def[x].zip = 1;
				scanf(" %s %s", s1, s2);
				def[x].a[0] = toupper(s1[0]) - 'A';
				def[x].a[1] = toupper(s2[0]) - 'A';
				continue;
			}

			def[x].zip = 0;
			for (i = 0; !isalpha(s1[0]); i++) {
				sscanf(s1, "%d", &def[x].a[i]);
				scanf(" %s", s1);
			}
			def[x].m = i;
			def[x].a[i] = toupper(s1[0]) - 'A';
		}

		for (i = 0; i < 26; i++)
			if (def[i].defined) def[i].cycle = findcyc(i);

		while (m-- > 0 && scanf(" %s %d %d", s1, &x, &y) == 3) {
			n = toupper(s1[0]) - 'A';
			for (i = 0; (x + i) <= y; i++)
				printf(i ? " %d" : "%d", eval(n, x + i));
			printf("\n");
		}

		if (t > 0) printf("\n");
	}

	return 0;
}
