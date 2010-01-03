#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>
#include <deque>
#include <iostream>
#include <set>
#include <map>
using namespace std;
#define FOREACH(it,v) for(__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

double EPS = 1e-9, INF = 1e999;
double a[64][64];
int n, m, isBasic[64], rowsBasic[64];

double simplex()
{
	int i, j, k, e;
	double ratio, temp;

	while (true) {
/*		printf("\n");
		for (i = 0; i <= m; i++) {
			for (j = 0; j <= n+m; j++) printf("%7.2f ", a[i][j]);
			printf("\n");
		}*/

		// choose entering varible
		e = -1;
		for (i = 0; i < n+m; i++) {
			if (!isBasic[i] && a[m][i] > EPS) {
				if (e == -1 || a[m][i] > a[m][e] + EPS) e = i;
			}
		}
		if (e < 0) break;

		// choose leaving variable
		ratio = INF;
		k = -1;
		for (i = 0; i < m; i++) {
			if (a[i][e] < EPS) continue;
			temp = a[i][n+m] / a[i][e];
			if (temp < ratio) {
				ratio = temp;
				k = i;
			}
		}
		if (k < 0) return INF;   // unbounded

//printf("<z=%.5f, e=%d l=%d ratio=%.3lf>\n", -a[m][n+m], e, rowsBasic[k], ratio);

		// pivot

		for (i = 0; i <= n+m; i++)
			if (i != e) a[k][i] /= a[k][e];
		a[k][e] = 1;

		for (i = 0; i <= m; i++) {
			if (i == k) continue;
			temp = a[i][e];
			for (j = 0; j <= n+m; j++)
				a[i][j] -= temp * a[k][j];
			a[i][e] = 0;
		}

		isBasic[rowsBasic[k]] = 0;
		isBasic[e] = 1;
		rowsBasic[k] = e;
	}

	return -a[m][n+m];
}

int main()
{
	int i, j;
	while (scanf("%d %d", &n, &m) == 2 && n >= 1) {
		memset(a, 0, sizeof(a));
		memset(isBasic, 0, sizeof(isBasic));
		for (i = 0; i < n; i++)
			scanf("%lf", &a[m][i]);
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++)
				scanf("%lf", &a[i][j]);
			scanf("%lf", &a[i][n+m]);
			a[i][n + i] = 1;
			isBasic[n + i] = 1;
			rowsBasic[i] = n + i;
		}
		printf("Nasa can spend %d taka.\n", (int)ceil(simplex() * m));
	}
}
