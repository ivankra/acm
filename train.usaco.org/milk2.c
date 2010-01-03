/*
ID: infnty1
PROB: milk2
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct { int a, b; } pair;
pair X[5001];

int cmp(const void *p, const void *q) {
	pair *P=(pair *)p, *Q=(pair *)q;
	return (P->a!=Q->a) ? (P->a - Q->a) : (P->b - Q->b);
}

int max(int x, int y) { return x>y?x:y; }

int main()
{
	int i, n, s, e, M, I;

	freopen("milk2.in", "r", stdin);
	freopen("milk2.out", "w", stdout);

	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%d %d", &X[i].a, &X[i].b);

	qsort(X, n, sizeof(X[0]), &cmp);

	M = I = 0;
	s = e = X[0].a;
	for (i = 0;; i++) {
		I = max(I, X[i].a - e);
		M = max(M, e - s);
		if (i >= n) break;
		if (X[i].a > e) e = s = X[i].a;
		e = max(e, X[i].b);
	}

	printf("%d %d\n", M, I);
	return 0;
}
