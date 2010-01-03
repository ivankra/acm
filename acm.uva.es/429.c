#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOPATH 0x7FFFFFFF

static char dict[256][16];
static int t, n, m[256][256], len[256];

static int find(char *w)
{
	register int a, b, c, r;

	for (a = 0, b = n - 1; a < b;) {
		c = (a + b) >> 1;

		r = strcmp(dict[c], w);
		if (r < 0)
			a = c + 1;
		else if (r > 0)
			b = c - 1;
		else
			return c;
	}

	if (strcmp(dict[a], w) == 0)
		return a;

for (w=NULL;;)*w++=0;
}

int main()
{
	static char line[1024], w1[16], w2[16];
	int i, j, k;

	scanf("%d", &t);

	while (t-- > 0) {
		memset(dict, '\0', sizeof(dict));
		for (n = 0; scanf(" %15[a-zA-Z*] \n", dict[n]) == 1; n++) {
			for (i = 0; dict[n][i] && dict[n][i] != '*'; i++);
			if (i == 0 || dict[n][i] == '*') break;
		}

		qsort(dict, n, sizeof(dict[0]), strcmp);

		for (i = 0; i < n; i++)
			len[i] = strlen(dict[i]);

		for (i = 0; i < n; i++) {
			m[i][i] = 0;
			for (j = 0; j < i; j++) {
				char *p, *q;

				if (len[i] != len[j]) {
					m[j][i] = m[i][j] = NOPATH;
					continue;
				}

				for (k = 0, p = dict[i], q = dict[j]; *p;)
					if (*p++ != *q++ && ++k >= 2) break;

				m[i][j] = m[j][i] = (k <= 1) ? 1 : NOPATH;
			}
		}

		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				if (m[i][k] == NOPATH || i == k) continue;
				for (j = 0; j < i; j++) {
					if (m[k][j] == NOPATH) continue;
					if (m[i][j] > (m[i][k] + m[k][j])) {
						m[i][j] = m[i][k] + m[k][j];
						m[j][i] = m[i][j];
					}
				}
			}
		}

		while (fgets(line, sizeof(line), stdin)) {
			if (sscanf(line,"%14[a-zA-Z] %14[a-zA-Z]",w1,w2) != 2)
				break;

			printf("%s %s %d\n", w1, w2, m[find(w1)][find(w2)]);
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}
