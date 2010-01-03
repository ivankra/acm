#include <stdio.h>
#include <stdlib.h>

#define N 16384

struct { int l, r, a; } p[N];
struct { int x, p; } ev[2*N];
int heap[N], loc[N], sz, n, m;

void up(int p)
{
	int v = heap[p];
	for (; p > 1 && heap[p>>1] < v; p>>=1) loc[heap[p] = heap[p>>1]] = p;
	loc[heap[p] = v] = p;
}

void down(int p)
{
	int q, r;
	for (; (q=2*p) <= sz; p = r) {
		r = (heap[p] >= heap[q]) ? p : q;
		if (++q <= sz && heap[q] > heap[r]) r = q;
		if (p == r) break;
		q = heap[p];
		loc[heap[p] = heap[r]] = p;
		loc[heap[r] = q] = r;
	}
}

void add(int r) { sz++; loc[heap[sz] = r] = sz; up(sz); }
void rm(int r) { if(--sz>0){ r=loc[r]; loc[heap[r]=heap[sz+1]]=r; down(r); up(r); }}

int cmp(const void *p, const void *q) { return *(int *)p - *(int *)q; }

int main()
{
	int i, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (m = 0, i = 1; i <= n; i++) {
			scanf("%d %d", &p[i].l, &p[i].r); p[i].a = 0;
			ev[m].x = p[i].l; ev[m++].p = i;
			ev[m].x = p[i].r+1; ev[m++].p = -i;
		}

		qsort(ev, m, sizeof(ev[0]), &cmp);

		for (sz = i = 0; i < m; i++) {
			if (ev[i].p > 0) add(ev[i].p); else rm(-ev[i].p);
			if ((i == m-1 || ev[i+1].x != ev[i].x) && sz > 0) p[heap[1]].a = 1;
		}

		for (m = 0, i = 1; i <= n; i++) m += p[i].a;
		printf("%d\n", m);
	}

	return 0;
}
