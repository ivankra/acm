#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct { int n, a[128]; } poly_t;

int inv[2048], m;

void copy(poly_t *r, poly_t *s)
{
	int i;
	for (r->n = s->n, i = 0; i <= s->n; i++) r->a[i] = s->a[i];
}

void reduce(poly_t *p)
{
	int i;
	for (i = p->n; i >= 0; i--) p->a[i] %= m;
	while (p->n > 0 && p->a[p->n] == 0) p->n--;
}

void prn(poly_t *p)
{
	int i;
	for (i = p->n; i > 0; i--)
		if (p->a[i]) printf("%s%d x^%d", (i == p->n) ? "" : " + ", p->a[i], i);
	printf("%s%d", (p->n == 0) ? "" : " + ", p->a[0]);
}

void divide(poly_t *Q, poly_t *A, poly_t *B)
{
	int i, j, k, d;

	if (A->n < B->n) {
		if (Q) Q->n = 0;
		return;
	}

	i = A->n - B->n;
	if (Q) Q->n = i;

	for (; i >= 0; i--) {
		d = (A->a[B->n + i] * inv[B->a[B->n]]) % m;
		if (Q) Q->a[i] = d;
		if (d == 0) continue;

		for (j = B->n + i, k = B->n; j >= 0 && k >= 0; j--, k--)
			A->a[j] = (A->a[j] - ((d * B->a[k]) % m) + m) % m;
	}

	if (Q) reduce(Q);
	reduce(A);
}

void getpoly(poly_t *p)
{
	int i;

	memset(p, 0, sizeof(poly_t));

	scanf("%d", &p->n);
	for (i = p->n; i >= 0; i--) scanf("%d", &p->a[i]);
	reduce(p);
}

void gcdext(int a, int b, int *x, int *y, int *d)
{
	if (a < 0) {
		gcdext(-a, b, x, y, d);
		*x = -(*x);
	} else if (b < 0) {
		gcdext(a, -b, x, y, d);
		*y = -(*y);
	} else if (b == 0) {
		*x = 1;
		*y = 0;
		*d = a;
	} else {
		gcdext(b, a % b, y, x, d);
		*y -= (a / b) * (*x);
	}
}

int modinv(int a, int m)
{
	int x, y, d;

	gcdext(a, m, &x, &y, &d);
	if (d != 1) return -1;

	return (x < 0) ? (m - (-x) % m) : (x % m);
}

poly_t *polygcd(poly_t *A, poly_t *B)
{
	poly_t *T;

	for (;;) {
		if (A->n < B->n) { T = A; A = B; B = T; }
		if (B->n == 0) {
			if (B->a[0] != 0) { A->n = 0; A->a[0] = 1; }
			return A;
		}
		divide(NULL, A, B);
	}
}

int main()
{
	int i, t;
	poly_t A, B, *G;

	for (t = 1; scanf("%d", &m) == 1 && m > 0; t++) {
		assert(m < 2048);

		inv[0] = 0;
		for (i = 1; i < m; i++)
			inv[i] = modinv(i, m);

		getpoly(&A);
		getpoly(&B);

		G = polygcd(&A, &B);

		reduce(G);

		if (G->a[G->n] != 0) {
			for (i = 0; i <= G->n; i++)
				G->a[i] = (G->a[i] * inv[G->a[G->n]]) % m;
		}
		reduce(G);

		printf("Case %d: %d", t, G->n);
		for (i = G->n; i >= 0; i--) printf(" %d", G->a[i]);
		printf("\n");
	}

	return 0;
}
