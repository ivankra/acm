#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct { int x, y1, y2; } rec_t;
typedef struct { int x, y; } pt_t;

struct { int x1, y1, x2, y2; } B[64];
int n, m;

rec_t rx[128], ry[128];



int cmp(const void *p, const void *q)
{
	return ((rec_t *)p)->x - ((rec_t *)q)->x;
}

void solve()
{
	int i;

	for (m = 0, i = 0; i < n; i++) {
		rx[m].x = B[i].x1;
		rx[m].y1 = B[i].y1;
		rx[m].y2 = B[i].y2;
		m++;
		rx[m].x = B[i].x2;
		rx[m].y1 = B[i].y1;
		rx[m].y2 = B[i].y2;
		m++;
	}
	rx[m].x = B[n].x2;
	rx[m].y1 = rx[m].y2 = B[n].y2;
	m++;
	qsort(rx, m, sizeof(rx[0]), &cmp);

	for (m = 0, i = 0; i < n; i++) {
		ry[m].x = B[i].y1;
		ry[m].y1 = B[i].x1;
		ry[m].y2 = B[i].x2;
		m++;
		ry[m].x = B[i].y2;
		ry[m].y1 = B[i].x1;
		ry[m].y2 = B[i].x2;
		m++;
	}
	rx[m].x = B[n].y2;
	rx[m].y1 = rx[m].y2 = B[n].x2;
	m++;
	qsort(ry, m, sizeof(ry[0]), &cmp);



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
