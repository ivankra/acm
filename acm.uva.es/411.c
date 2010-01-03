#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct {
	int id, a, d, x, y;
} seg[1024];

struct {
	int x, y, n;
	char d;
} cen[1024];

int crash[32][32], ncen, nseg, nact;
int dx[256], dy[256];

void check()
{
	static int z[32][32];
	int i;

	memcpy(z, crash, sizeof(crash));

	for (i = 0; i < nseg; i++) {
		if (seg[i].a == 0)
			continue;

		if (seg[i].x < 0 || seg[i].x > 29 ||
		    seg[i].y < 0 || seg[i].y > 29) {
			seg[i].a = 0;
			nact--;
			continue;
		}

		if (z[seg[i].y][seg[i].x]++ != 0)
			crash[seg[i].y][seg[i].x] = 1;
	}

	for (i = 0; i < nseg; i++) {
		if (seg[i].a && crash[seg[i].y][seg[i].x]) {
			seg[i].a = 0;
			nact--;
		}
	}
}

int main()
{
	int i, j;

	memset(dx, 0, sizeof(dx));
	memset(dy, 0, sizeof(dy));
	dx['L'] = -1;
	dx['R'] = 1;
	dy['U'] = 1;
	dy['D'] = -1;

	while (scanf("%d", &ncen) == 1 && ncen > 0) {
		for (i = 0; i < ncen; i++)
			scanf(" %c %d %d %d", &cen[i].d, &cen[i].n, &cen[i].x, &cen[i].y);

		for (nseg = nact = 0, i = 0; i < ncen; i++) {
			cen[i].d = toupper(cen[i].d);
			for (j = 0; j < cen[i].n; j++) {
				seg[nseg].id = i;
				seg[nseg].a = 1;
				seg[nseg].d = (int)cen[i].d;
				seg[nseg].x = cen[i].x - j * dx[cen[i].d];
				seg[nseg].y = cen[i].y - j * dy[cen[i].d];
				nseg++;
				nact++;
			}
		}
		
		memset(crash, 0, sizeof(crash));
		check();

		while (nact > 0) {
			for (i = 0; i < nseg; i++) {
				if (seg[i].a == 0) continue;
				seg[i].x += dx[seg[i].d];
				seg[i].y += dy[seg[i].d];
				if ((i + 1) < nseg && seg[i + 1].id != seg[i].id)
					check();
			}
			check();
		}

		printf("   0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2\n");
		printf("   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n");

		for (i = 29; i >= 0; i--) {
			printf("%.2d", i);
			for (j = 0; j < 30; j++) printf(crash[i][j] ? " X" : " .");
			printf("\n");
		}

		printf("\n");
	}

	return 0;
}
