/*
ID: mjf28791
PROG: packrec
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>

int w[4], h[4], best, nbest;

struct rect {
	int p, q;
} rects[65536];

void pack(int p, int q)
{
	int i;

	if (p > q) {
		i = p;
		p = q;
		q = i;
	}

	if (best < (p * q))
		return;

	if (best > (p * q)) {
		best = p * q;
		nbest = 1;
		rects[0].p = p;
		rects[0].q = q;
		return;
	}

	for (i = 0; i < nbest; i++)
		if (rects[i].p == p && rects[i].q == q) return;

	rects[nbest].p = p;
	rects[nbest].q = q;
	nbest++;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

void sol()
{
	pack(max(h[0], max(h[1], max(h[2], h[3]))), w[0] + w[1] + w[2] + w[3]);
	pack(h[0] + max(h[1], max(h[2], h[3])), max(w[0], w[1] + w[2] + w[3]));
	pack(max(h[0], h[1] + max(h[2], h[3])), w[0] + max(w[1], w[2] + w[3]));
	pack(max(h[0], max(h[1] + h[2], h[3])), w[0] + max(w[1], w[2]) + w[3]);
	pack(max(h[0] + h[1], max(h[2], h[3])), max(w[0], w[1]) + w[2] + w[3]);

	if (w[1] <= w[0] && h[0] <= h[2] && (w[1] + w[3]) <= (w[0] + w[2]))
		pack(max(h[0] + h[1], h[2] + h[3]), w[0] + w[2]);

	if ((h[0] + h[1]) <= h[2] && w[1] <= w[0])
		pack(h[2] + h[3], max(w[0] + w[2], w[3]));
}

int cmp(const void *a, const void *b)
{
	struct rect *x = (struct rect *)a, *y = (struct rect *)b;
	return (x->p != y->p) ? (x->p - y->p) : (x->q - y->q);
}

int main()
{
	int x[2][4], p[4], i, j, k;

	freopen("packrec.in", "r", stdin);
	freopen("packrec.out", "w", stdout);

	for (i = 0; i < 4; i++)
		scanf("%d %d", &x[0][i], &x[1][i]);

	for (i = 0; i < 4; i++)
		p[i] = i;

	for (best = 0x7FFFFFFF, nbest = 0;;) {
		for (k = 0; k < 16; k++) {
			for (i = 0; i < 4; i++) {
				w[i] = x[(k >> i) & 1][p[i]];
				h[i] = x[((k >> i) & 1) ^ 1][p[i]];
			}
			sol();
		}

		for (j = 2; j >= 0 && p[j] > p[j + 1]; j--);
		if (j < 0) break;

		for (i = 3; p[i] < p[j]; i--);

		k = p[i];
		p[i] = p[j];
		p[j] = k;

		for (j++, i = 3; j < i;) {
			k = p[i];
			p[i--] = p[j];
			p[j++] = k;
		}
	}

	qsort(rects, nbest, sizeof(rects[0]), &cmp);

	printf("%d\n", best);
	for (i = 0; i < nbest; i++)
		printf("%d %d\n",rects[i].p, rects[i].q);

	return 0;
}
