#include <stdio.h>

static struct {
	char name[8];
	int s[6];
} config[6] = { /* b  g  c   b  g  c   b  g  c */
	{ "BCG", {    1, 2,  3, 4,     6,    8 } },
	{ "BGC", {    1, 2,  3,    5,  6, 7    } },
	{ "CBG", { 0, 1,        4, 5,  6,    8 } },
	{ "CGB", { 0, 1,     3,    5,     7, 8 } },
	{ "GBC", { 0,    2,     4, 5,  6, 7    } },
	{ "GCB", { 0,    2,  3, 4,        7, 8 } }
};

int main()
{
	int i, j, s, m, v, b[9];

	for (;;) {
		for (i = 0; i < 9; i++)
			if (scanf("%d", &b[i]) < 1) break;

		if (i < 9)
			break;

		for (i = 0, v = 0; i < 6; i++) {
			for (j = 0, s = 0; j < 6; j++)
				s += b[config[i].s[j]];

			if (i == 0 || v > s) {
				v = s;
				m = i;
			}
		}

		printf("%s %d\n", config[m].name, v);
	}

	return 0;
}
