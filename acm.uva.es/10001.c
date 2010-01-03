#include <stdio.h>
#include <stdlib.h>

#define DERIVE(L, C, R, rule) ((rule >> (((L) << 2) | ((C) << 1) | (R))) & 1)

static int find(int r, int w, char s[])
{
	static int a[256];
	int i;

	for (i = 0; i < w; i++)
		a[i] = -1;

	for (i = 0;;) {
		if (i == w) {
			if ((DERIVE(a[w - 1], a[0], a[1], r) == s[0]) &&
			    (DERIVE(a[w - 2], a[w - 1], a[0], r) == s[w-1])) {
				return 1;
			}
			i--;
			continue;
		}

		if (a[i] == 1) {
			if (i-- <= 0)
				return 0;
			continue;
		}

		a[i]++;

		if (i >= 2 && DERIVE(a[i - 2], a[i - 1], a[i], r) != s[i - 1])
			continue;

		a[++i] = -1;
	}
}

int main()
{
	static char state[256];
	int rule, width, i, c;

	while (scanf("%d %d", &rule, &width) >= 2) {
		while ((c = getchar()) != EOF && c != '0' && c != '1');

		for (i = 0; c == '0' || c == '1'; i++, c = getchar())
			state[i] = c - '0';

		while (i < width)
			state[i++] = 0;

		if (find(rule, width, state))
			printf("REACHABLE\n");
		else
			printf("GARDEN OF EDEN\n");
	}

	return 0;
}
