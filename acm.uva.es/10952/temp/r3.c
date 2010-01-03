#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int p[16][16], q[16][16], w=6, h=6, t=100;

int check()
{
	static int c[256];
	int i, j;

	c['X'] = c['O'] = 0;

	for (i = 1; i <= h; i++)
		for (j = 1; j <= w; j++)
			c[p[i][j]]++;

	for (i = 1; i <= h; i++)
		for (j = 1; j <= w; j++)
			c[q[i][j]]--;

	if (c['X'] != 0 || c['O'] != 0) return 0;

	for (i = 1; i <= h; i++)
		for (j = 1; j <= w; j++) {
			if (p[i][j] == '.') continue;
			if (q[i][j] == p[i][j]) continue;
			if (q[i-1][j] == p[i][j]) continue;
			if (q[i+1][j] == p[i][j]) continue;
			if (q[i][j-1] == p[i][j]) continue;
			if (q[i][j+1] == p[i][j]) continue;
			return 0;
		}

	for (i = 1; i <= h; i++)
		for (j = 1; j <= w; j++) {
			if (q[i][j] == '.') continue;
			if (p[i][j] == q[i][j]) continue;
			if (p[i-1][j] == q[i][j]) continue;
			if (p[i+1][j] == q[i][j]) continue;
			if (p[i][j-1] == q[i][j]) continue;
			if (p[i][j+1] == q[i][j]) continue;
			return 0;
		}

	return 1;
}

int main()
{
	int i, j;

	srand(time(NULL));

	printf("%d\n", t);

	memset(p, 0, sizeof(p));
	memset(q, 0, sizeof(q));

	while (t-- > 0) {
		printf("%d %d", w, h);

		do {
			for (i = 1; i <= h; i++)
				for (j = 1; j <= w; j++) {
					p[i][j] = "OX"[rand() % 2];
					q[i][j] = "OX"[rand() % 2];
				}
		} while (!check());

		for (i = 1; i <= h; i++) {
			printf("  ");
			for (j = 1; j <= w; j++)
				putchar(p[i][j]);
			putchar(' ');
			for (j = 1; j <= w; j++)
				putchar(q[i][j]);
		}
		printf("\n");
	}

	return 0;
}
