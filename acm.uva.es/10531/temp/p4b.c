#include <stdio.h>
#include <assert.h>

#define EPS 1e-10

int fgot[8][1024], enforce_r, enforce_b, id, n, m;
double P[8][8], R[8][8], ftab[8][1024], xtab[8][1024];

int jtab[6][1024][32];

int min(int x, int y) { return (x < y) ? x : y; }
int max(int x, int y) { return (x > y) ? x : y; }

int join(int A, int B)
{
	int a[8], b[8], c[8], i, j, k, t, s, chg;

	for (i = 0; i < m; i++) {
		a[i] = (A >> (2 * i)) & 3;
		b[i] = (B >> i) & 1;
		c[i] = 0;

	}

/*printf("join ");
printf(" a=(");for(i=0;i<m;i++)printf(i?" %d":"%d",a[i]);printf(")");
printf(" b=(");for(i=0;i<m;i++)printf(i?" %d":"%d",b[i]);printf(")");
  */
	for (i = 0; i < m; i++) {
		if (a[i] != 1) continue;
		for (j = i; j >= 0 && b[j] == 0; j--) c[j] = 1;
		for (j = i; j < m && b[j] == 0; j++) c[j] = 1;
	}

	for (i = 0; i < m && c[i] != 1; i++);
	if (i >= m) { /*printf("  => 0\n");*/ return 0;}

	for (i = 0, k = 1;;) {
		while (i < m && (b[i] || c[i])) i++;
		if (i >= m) break;
		for (k++; i < m && b[i] == 0; i++) c[i] = k;
	}

	do {
		chg = 0;
		for (i = 0; i < m; i++) {
			for (j = i + 1; j < m; j++) {
				if (c[i] != c[j] || c[i] == 0) continue;
				if (a[i] == a[j] || a[i] == 0 || a[j] == 0) continue;
				t = max(a[i], a[j]); s = min(a[i], a[j]);
				for (k = 0; k < m; k++)
					if (a[k] == t) { a[k] = s; chg = 1; }
			}
		}

		for (i = 0; i < m; i++) {
			for (j = i + 1; j < m; j++) {
				if (a[i] != a[j] || a[i] == 0) continue;
				if (c[i] == c[j] || c[i] == 0 || c[j] == 0) continue;
				t = max(c[i], c[j]); s = min(c[i], c[j]);
				for (k = 0; k < m; k++)
					if (c[k] == t) { c[k] = s; chg = 1; }
			}
		}
	} while (chg);

	for (k = 0, i = 0; i < m; i++)
		k |= c[i] << (2 * i);

/*printf("  c=(");for(i=0;i<m;i++)printf(i?" %d":"%d",c[i]);printf(")");
printf("\n");*/

/*printf("j m=%d A=%.4X B=%.4X C=%.4X\n",m,A,B,k);*/

	return k;
}

double f(int r, int A)
{
	int i, B;
	double p;

	if (fgot[r][A] == id) return ftab[r][A];
	fgot[r][A] = id;

/*printf("f(r=%d, A=%.4X)\n",r,A);*/

	if (r == n) return ftab[r][A] = (((A>>(2*(m-1)))&3)==1) ? 1. : 0.;
	if (A == 0) return ftab[r][A] = 0.;

	ftab[r][A] = 0.;
	for (B = 0; B < (1 << m); B++) {
		for (p = 1., i = 0; i < m; i++)
			p *= (B & (1 << i)) ? P[r][i] : (1. - P[r][i]);
		if (p < EPS) continue;
if(jtab[m][A][B]!=join(A,B)) {
  printf("m=%d A=%.4X b=%.4X   jtab=%d  join=%d\n",m,A,B,jtab[m][A][B],join(A,B));
  exit(0);
}
		ftab[r][A] += p * f(r+1, join(A,B));
	}

/*printf("f(r=%d, A=%.4X) = %.5f\n",r,A,ftab[r][A]);*/
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
int k=0;
t=clock();

	for (m = 1; m <= 5; m++)
		for (i = 0; i < (1 << (2 * m)); i++)
			for (j = 0; j < (1 << m); j++)
				{k++;jtab[m][i][j] = join(i, j);}
printf("[%d]  %d\n",clock()-t,k);

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
