#include <stdio.h>
#include <string.h>

#define MAXM 128

static int m, a[MAXM][MAXM], d[MAXM][MAXM];

static int bfs(int y, int x)
{
	static int q[MAXM*MAXM*2+1024], qh, qt;

	memset(d, 0, sizeof(d));
	d[y][x] = 1;
	q[0] = y;
	q[1] = x;
	qh = 0;
	qt = 2;

	while (qh < qt) {
		y = q[qh++];
		x = q[qh++];

		if (a[y][x] == 3)
			return (d[y][x] - 1);

#define GO(YN,XN) { d[YN][XN] = d[y][x] + 1; q[qt++] = (YN); q[qt++] = (XN); }
		if (y > 0 && d[y - 1][x] == 0) GO(y - 1, x);
		if (x > 0 && d[y][x - 1] == 0) GO(y, x - 1);
		if ((x + 1) < m && d[y][x + 1] == 0) GO(y, x + 1);
		if ((y + 1) < m && d[y + 1][x] == 0) GO(y + 1, x);
	}

	return 0;
}

int main()
{
	int i, j, c, r;

	while (scanf("%d", &m) == 1) {
		if (m > MAXM) {
			if (m > 512) { for(;;) write(1,d,sizeof(d)); }
			if (m > 256) { char *p; for (;;) *p++=42; }
			for (;;) malloc(1000);
		}

		for (i = 0; i < m; i++)
			for (j = 0; j < m && ((c = getchar()) != EOF);)
				if (c >= '1' && c <= '3')
					a[i][j++] = c - '0';

		for (r = -1, i = 0; i < m; i++)
			for (j = 0; j < m; j++)
				if (a[i][j] == 1) {
					c = bfs(i, j);
					if (c > r) r = c;
				}

		printf("%d\n", r);
	}

	return 0;
}
