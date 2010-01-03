#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int read(int, char *, int);

char *facename[] = { "front", "back", "left", "right", "top", "bottom" };
int opposite[] = { 1, 0, 3, 2, 5, 4 };

int ncubes, cube[1024][8];
int cid[8192], cface[8192], cpred[8192], cheight[8192], best[128];

static void solve()
{
	static int p[8192];
	int i, j, k;

	for (i = 0; i <= 100; i++)
		best[i] = 0;

	cheight[0] = 0;
	for (k = 1, i = 0; i < ncubes; i++) {
		for (j = 0; j < 6; j++) {
			cid[k + j] = i;
			cface[k + j] = j;
			cpred[k + j] = best[cube[i][j]];
			cheight[k + j] = 1 + cheight[cpred[k + j]];
		}

		for (j = 0; j < 6; j++, k++)
			if (cheight[k] > cheight[best[cube[i][opposite[j]]]])
				best[cube[i][opposite[j]]] = k;
	}

	for (j = i = 1; i < k; i++)
		if (cheight[i] > cheight[j]) j = i;

	printf("%d\n", cheight[j]);

	for (i = 0; j > 0; j = cpred[j])
		p[i++] = j;

	while (i-- > 0)
		printf("%d %s\n", cid[p[i]] + 1, facename[cface[p[i]]]);
}

void main2()
{
	static char inbuf[1048576];
	static int isdig[256];
	char *inp;
	int i, r, t;

	read(0, inp = inbuf, sizeof(inbuf));
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

#define READ(x) \
	{ while (!isdig[*inp]) inp++; \
	  for (r = *inp++ - '0'; isdig[*inp];) r = r * 10 + *inp++ - '0'; x = r; }

	for (t = 1;; t++) {
		READ(ncubes);
		if (ncubes == 0) break;

		for (i = 0; i < ncubes; i++) {
			READ(cube[i][0]);
			READ(cube[i][1]);
			READ(cube[i][2]);
			READ(cube[i][3]);
			READ(cube[i][4]);
			READ(cube[i][5]);
		}

		printf(((t == 1) ? "Case #%d\n" : "\nCase #%d\n"), t);
		solve();
	}

	exit(0);
}

int main()
{
	main2();
	return 0;
}
