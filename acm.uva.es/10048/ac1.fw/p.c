#include <stdio.h>

static int map[128][128];

#define NOPATH 0x7FFFFFFF

#undef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

#undef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

int main()
{
	static int c, s, q, r, t1, t2, t3;
	int i, j, k, m;

	for (r = 1; scanf("%d %d %d", &c, &s, &q) >= 3 && c && s && q; r++) {
		for (i = 0; i < 128; i++)
			for (j = 0; j < 128; j++)
				map[i][j] = (i == j) ? 0 : NOPATH;

		for (i = 0; i < s; i++) {
			scanf("%d %d %d", &t1, &t2, &t3);
			map[t1][t2] = t3;
			map[t2][t1] = t3;
		}

		for (i = 1; i <= c; i++) {
			for (j = 1; j <= c; j++) {
				for (k = 1; k < j; k++) {
					m = MAX(map[j][i], map[i][k]);
					m = MIN(map[j][k], m);
					map[j][k] = m;
					map[k][j] = m;
				}
			}
		}

		printf((r == 1) ? "Case #1\n" : "\nCase #%d\n", r);

		for (i = 0; i < q; i++) {
			scanf("%d %d", &t1, &t2);
			if (map[t1][t2] == NOPATH)
				printf("no path\n");
			else
				printf("%d\n", map[t1][t2]);
		}
	}

	return 0;
}
