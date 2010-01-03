#include <stdio.h>
#include <assert.h>

#define EPS 1e-10

int fgot[8][1024], enforce_r, enforce_b, id, n, m;
double P[8][8], R[8][8], ftab[8][1024], xtab[8][1024];

int join(int A, int B)
{
	int C, i, j, k, u, v, s;

	C = 0;

	for (i = 0; i < m; i++) {
		if (((A >> (2 * i)) & 3) != 1) continue;

		for (j = i; j >= 0 && ((B >> j) & 1) == 0; j--)
			C |= 1 << (2 * j);

		for (j = i+1; j < m && ((B >> j) & 1) == 0; j++)
			C |= 1 << (2 * j);
	}

	if (C == 0)
		return 0;

printf("join A={");
for(i=0;i<m;i++)printf(" %d",(A>>(2*i))&3);
printf(" }  B={");
for(i=0;i<m;i++)printf(" %d",(B>>i)&1);
printf(" }   C0={");
for(i=0;i<m;i++)printf(" %d",(C>>(2*i))&3);
printf(" }   C={");

	for (i = 0, k = 1;;) {
		for (; i < m; i++)
			if (((B >> i) & 1) == 0 && ((C >> (2 * i)) & 3) == 0) break;
		if (i >= m) break;

		for (k++; i < m && ((B >> i) & 1) == 0; i++)
			C |= k << (2 * i);
	}

	do {
		s = 0;
		for (i = 0; i < m; i++) {
			if (((A>>(2*i))&3)==0) continue;
			for (j = i + 1; j < m; j++) {
				if (((A>>(2*i))&3) != ((A>>(2*j))&3)) continue;

				u = ((C>>(2*i))&3); v = ((C>>(2*j))&3);
				if (u == v || u == 0 || v == 0) continue;
				if (u < v) { k = u; u = v; v = k; }

				for (k = 0; k < m; k++) {
					if (((C>>(2*k))&3) != u) continue;
					C &= ~(3 << (2*k));
					C |= v << (2*k);
					s++;
				}
			}
		}

		for (i = 0; i < m; i++) {
			if (((C>>(2*i))&3)==0) continue;
			for (j = i + 1; j < m; j++) {
				if (((C>>(2*i))&3) != ((C>>(2*j))&3)) continue;

				u = ((A>>(2*i))&3); v = ((A>>(2*j))&3);
				if (u == v || u == 0 || v == 0) continue;
				if (u < v) { k = u; u = v; v = k; }

				for (k = 0; k < m; k++) {
					if (((A>>(2*k))&3) != u) continue;
					A &= ~(3 << (2*k));
					A |= v << (2*k);
					s++;
				}
			}
		}
	} while (s > 0);

for(i=0;i<m;i++)printf(" %d",(C>>(2*i))&3);
printf("}\n");

	return C;
}

double f(int r, int A)
{
	int i, B;
	double p;

	if (fgot[r][A] == id) return ftab[r][A];
	fgot[r][A] = id;

printf("f(r=%d, A=%.4X)\n",r,A);

	if (r == n) return ftab[r][A] = (((A >> (m - 1)) & 1) ? 1. : 0.);
	if (A == 0) return ftab[r][A] = 0.;

	ftab[r][A] = 0.;
	for (B = 0; B < (1 << m); B++) {
		for (p = 1., i = 0; i < m; i++)
			p *= (B & (1 << i)) ? P[r][i] : (1. - P[r][i]);
		if (p < EPS) continue;

		ftab[r][A] += p * f(r+1, join(A,B));
	}

printf("f(r=%d, A=%.4X) = %.5f\n",r,A,ftab[r][A]);
	return ftab[r][A];
}

void solve()
{
	id++;
	printf("%.5f\n", f(0, 1));

}

int main()
{
	int i, j, t;

	id = 42;
	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &m, &n) == 2;) {
		assert(1 <= n && n <= 6 && 1 <= m && m <= 5);

		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				scanf("%lf", &P[j][i]);

		solve();

		if (t) printf("\n");
	}

	return 0;
}
