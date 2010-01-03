#include <cstdio>
#include <cassert>
#include <string>
#include <map>
#include <algorithm>
#define EPS 1e-12
using namespace std;

int n;
long double a[128][128], P;
char what[16], la[128][16], lb[128][16];
map<string, int> M;

long double Abs(long double x) { return (x < 0) ? (-x) : x; }

void reduce()
{
	int i, j, k, r, c;
	long double t;

	for (r = c = 0; r < n && c < n;) {
		for (i = j = r; i < n; i++)
			if (Abs(a[i][c]) > Abs(a[j][c])) j = i;

		if (Abs(a[j][c]) < EPS) { c++; continue; }

		if (j != r)
			for (i = 0; i <= n; i++) swap(a[r][i], a[j][i]);

		for (i = 0; i < c; i++) a[r][i] = 0.;
		for (i = c+1; i <= n; i++) a[r][i] /= a[r][c];
		a[r][c] = 1.;

		for (j = 0; j < n; j++) {
			if (j == r) continue;
			t = a[j][c];
			a[j][c] = 0.;
			for (k = c+1; k <= n; k++)
				a[j][k] -= t * a[r][k];
		}

		r++; c++;
	}
}

int main()
{
	int i, j, T;

	for (scanf("%d",&T); T-->0 && scanf("%d %Lf %s", &n, &P, what) == 3;) {
		M.clear();
		for (i = 0; i < n; i++) {
			scanf(" %s %s", la[i], lb[i]);
			M[la[i]] = i;
		}

		assert(M["end"] == n-1);

		for (i = 0; i < n; i++) {
			for (j = 0; j <= n; j++)
				a[i][j] = 0.;
			a[i][i] = 1;
		}
		a[M["start"]][n] += 1;

		for (i = 0; i < n-1; i++) {
			a[M[lb[i]]][i] -= P;
			a[i+1][i] -= 1-P;
		}

		reduce();

		j = M[what];
		for (i = 0; i < n; i++)
			if (a[i][j] > EPS) { P = a[i][n]; break; }

		printf("Expected number of times label %s is executed is %.5Lf\n",
			what, (long double)(P+EPS));
	}

	return 0;
}
