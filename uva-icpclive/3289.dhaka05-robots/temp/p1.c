#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct { int x1, y1, x2, y2; } B[64], C[64];
int down[128][128], right[128][128], n;

int cmp(const void *p, const void *q)
{
	return *(int *)p - *(int *)q;
}

int bfind(int x[], int n, int y)
{
	int a, b, c;

	for (a = 0, b = n - 1; a <= b;) {
		c = (a + b) >> 1;
		if (x[c] < y)
			a = c + 1;
		else if (x[c] > y)
			b = c - 1;
		else
			return c;
	}
	return -1;
}

void solve()
{
	static int rx[128], ry[128];
	int i, j, k, width, height;

	for (k = 0, i = 0; i < n; i++) {
		rx[k++] = B[i].x1;
		rx[k++] = B[i].x2;
	}
	rx[k++] = B[n].x1;
	rx[k++] = B[n].x2;

	for (k = 0, i = 0; i < n; i++) {
		ry[k++] = B[i].y1;
		ry[k++] = B[i].y2;
	}
	ry[k++] = B[n].y1;
	ry[k++] = B[n].y2;

	qsort(rx, k, sizeof(rx[0]), &cmp);
	qsort(ry, k, sizeof(ry[0]), &cmp);

	for (i = 0; i <= n; i++) {
		C[i].x1 = 1 + bfind(rx, k, B[i].x1);
		C[i].y1 = 1 + bfind(ry, k, B[i].y1);
		C[i].x2 = 1 + bfind(rx, k, B[i].x2);
		C[i].y2 = 1 + bfind(ry, k, B[i].y2);
	}

	for (i = width = height = 0; i <= n; i++) {
		if (C[i].x1 > width) width = C[i].x1;
		if (C[i].x2 > width) width = C[i].x2;
		if (C[i].y1 > height) height = C[i].y1;
		if (C[i].y2 > height) height = C[i].y2;
	}

	for (i = 0; i <= height; i++)
		for (j = 0; j <= width; j++)
			down[i][j] = 0;

	for (i = 0; i <= height; i++)
		for (j = 0; j <= width; j++)
			right[i][j] = 0;

	for (i = 0; i <= width; i++)
		down[height][i] = down[0][i] = 1;

	for (i = 0; i <= height; i++)
		right[i][width] = right[i][0] = 1;

	for (k = 0; k < n; k++) {
		for (i = C[k].y1; i < C[k].y2; i++)
			for (j = C[k].x1 + 1; j < C[k].x2; j++)
				down[i][j] = 1;

		for (i = C[k].y1 + 1; i < C[k].y2; i++)
			for (j = C[k].x1; j < C[k].x2; j++)
				right[i][j] = 1;
	}

{int y,x; for(y=0; y <= height; y++) {  for(x=0; x <= width; x++) {
    if (y == C[n].y1 && x == C[n].x1) printf("S");
    else if (y == C[n].y2 && x == C[n].x2) printf("E");
    else printf("."); printf(right[y][x] ? "*" : " "); }
  printf("\n");  for(x=0; x <= width; x++) printf(down[y][x] ? "* " : "  ");
  printf("\n");}printf("----------------------\n");}


}

int main()
{
	int i, c, t, q;

	for (scanf("%d", &t), c = 1; c <= t && scanf("%d", &n) == 1; c++) {
		printf("Labyrinth #%d\n", c);

		assert(0 <= n && n <= 60);

		for (i = 0; i < n; i++) {
			scanf("%d %d %d %d", &B[i].x1, &B[i].y1, &B[i].x2, &B[i].y2);
			assert(B[i].x1 < B[i].x2 && B[i].y1 < B[i].y2);
			B[i].x1 = B[i].x1 * 2 - 1;
			B[i].y1 = B[i].y1 * 2 - 1;
			B[i].x2 = B[i].x2 * 2 + 1;
			B[i].y2 = B[i].y2 * 2 + 1;
		}

		for (scanf("%d", &q); q-- > 0;) {
			scanf("%d %d %d %d", &B[n].x1, &B[n].y1, &B[n].x2, &B[n].y2);
			B[n].x1 *= 2; B[n].y1 *= 2; B[n].x2 *= 2; B[n].y2 *= 2;
			solve();
		}
	}

	return 0;
}
