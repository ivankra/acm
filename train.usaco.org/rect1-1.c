/*
ID: infnty1
PROB: rect1
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int x1, y1, x2, y2, c; } rect_t;
typedef struct { int y, r; } ev_t;

rect_t R[1024];
ev_t ev[2048];
int A[2501], xl[2048], xn, en, n;
int H[1024], Hp[1024], Hn;

void add(int r)
{
	int i;
	for (i = ++Hn; i > 1; i >>= 1)
		if (r > H[i >> 1]) Hp[H[i] = H[i >> 1]] = i; else break;
	Hp[H[i] = r] = i;
}

void del(int r)
{
	int i, j;

	if (Hn <= 1) { Hn = 0; return; }

	i = Hp[r];
	if (i == Hn) { Hn--; return; }

	Hp[H[i] = H[Hn--]] = i;
	H[Hn+1] = -1;
	r = H[i];

	for (; (i << 1) <= Hn; i = j) {
		j = (H[i<<1] > H[i]) ? (i<<1) : i;
		if (H[(i<<1)+1] > H[j]) j = (i << 1) + 1;

		if (j == i) break;

		Hp[H[i] = H[j]] = i;
		Hp[H[j] = r] = j;
	}

	for (; i > 1; i >>= 1)
		if (r > H[i >> 1]) Hp[H[i] = H[i >> 1]] = i; else break;
	Hp[H[i] = r] = i;
}

int icmp(const void *p, const void *q) { return *(int *)p - *(int *)q; }
int ecmp(const void *p, const void *q) { return ((ev_t *)p)->y - ((ev_t *)q)->y; }

int main()
{
	int i, j, k, y0;

	freopen("rect1.in", "r", stdin);
	freopen("rect1.out", "w", stdout);

	scanf("%d %d %d", &R[1].x2, &R[1].y2, &n);

	R[1].x1 = R[1].y1 = 0; R[1].c = 1;
	n++;
	for (i = 2; i <= n; i++)
		scanf("%d %d %d %d %d", &R[i].x1, &R[i].y1, &R[i].x2, &R[i].y2, &R[i].c);

	for (xn = en = 0, i = 1; i <= n; i++) {
		xl[xn++] = R[i].x1;
		xl[xn++] = R[i].x2;
		ev[en].y = R[i].y1; ev[en++].r = i;
		ev[en].y = R[i].y2; ev[en++].r = -i;
	}

	qsort(xl, xn, sizeof(xl[0]), &icmp);
	for (i = j = 0; i < xn; i++)
		if (i == 0 || xl[i-1] != xl[i]) xl[j++] = xl[i];
	xn = j;

	qsort(ev, en, sizeof(ev[0]), &ecmp);

	memset(A, 0, sizeof(A));

	xn--;
	for (i = 0; i < xn; i++) {
		Hn = 0;
		y0 = ev[0].y;

		for (j = 0; j < en; j++) {
			k = abs(ev[j].r);
			if (R[k].x2 < xl[i+1] || R[k].x1 > xl[i]) continue;

			if (Hn > 0)
				A[R[H[1]].c] += (ev[j].y - y0) * (xl[i+1] - xl[i]);
			y0 = ev[j].y;

			if (ev[j].r > 0)
				add(ev[j].r);
			else
				del(-ev[j].r);
		}
	}

	for (i = 1; i <= 2500; i++)
		if (A[i]) printf("%d %d\n", i, A[i]);

	return 0;
}
