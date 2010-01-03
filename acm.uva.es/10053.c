#include <stdio.h>
#include <string.h>
#include <math.h>
double pi;

double f(int l, int w, double a) { return w*cos(a)+l*sin(a); }

int fit4(int L, int W, int l, int w, double a)
{
	return w*cos(a)+l*sin(a) < L+1e-8 && w*sin(a)+l*cos(a) < W+1e-8;
}

int fit3(int L, int W, int l, int w, double a, double b, int q)
{
	double c;

	if (fit4(L,W,l,w,a) || fit4(L,W,l,w,b)) return 1;

	while (fabs(b - a) > 1e-15) {
		c = (a + b) / 2;
		if (fit4(L,W,l,w,c)) return 1;
		if ((f(l,w,c) > ((q&2)?L:W)) ^ (q&1)) a = c; else b = c;
	}

	return 0;
}

int fit2(int L, int W, int l, int w)
{
	double a[4], t;
	int i, j;

	if (w <= L && l <= W) return 1;
	if (l <= L && w <= W) return 1;

	a[0] = 0.;
	a[1] = atan(w / (double)l);
	a[2] = atan(l / (double)w);
	if (w > l) { t = a[1]; a[1] = a[2]; a[2] = t; }
	a[3] = pi/2.;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 4; j++)
			if (fit3(L,W,l,w,a[i],a[i+1],j)) return 1;

	return 0;
}

int fit1(int L, int W, int l, int w) { return fit2(L,W,l,w) || fit2(L,W,w,l); }
int fit(int L, int W, int l, int w) { return fit1(L,W,l,w) || fit1(W,L,l,w); }

int l[16], w[16], L[16], W[16], C[16], n, m;
int u[16], sol[16], best[16], bestv;

void go(int k, int c)
{
	int i;

	if (bestv >= 0 && bestv <= c) return;

	if (k == m) {
		bestv = c; memcpy(best, sol, sizeof(sol));
		return;
	}

	for (i = 0; i < n; i++)
		if (u[i]==0 && fit(L[i],W[i],l[k],w[k]))
			{ sol[k]=i; u[i]=1; go(k+1,c+C[i]); u[i]=0; }
}

int main()
{
	int i, t;

	pi = 2. * acos(0.);
	for (t = 1; scanf("%d %d", &m, &n) == 2 && m > 0; t++) {
		printf("%sCase #%d\n", t==1 ? "" : "\n", t);

		for (i = 0; i < m; i++) scanf("%d %d", &l[i], &w[i]);
		for (i = 0; i < n; i++) scanf("%d %d %d", &L[i], &W[i], &C[i]);

		bestv = -1;
		memset(u, 0, sizeof(u));
		go(0,0);

		if (bestv < 0)
			printf("cannot buy\n");
		else
			for (i = 0; i < m; i++) printf("%d\n", best[i]+1);
	}

	return 0;
}
