#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <deque>
#include <set>
using namespace std;
typedef long long LL;

int N;
double X[50], Y[50], dist[50][50], maxCap;
double food[50];
double EPS = 1e-6;

double sqr(double x) { return x*x; }

bool check(int buy)
{
	for (int i = 0; i < N; i++) food[i] = -1;
	food[0] = buy;

//printf("\n\nCheck %d\n", buy);

	while (true) {

//printf("\nNext iteration: food=");
//for (int i = 0; i < N; i++) printf(" %.3f", food[i]);
//printf("\n");

		if (food[N-1] > -0.5) return true;

		bool changed = false;

		for (int u = 0; u < N-1; u++) {
			if (food[u] < -0.5) continue;
			for (int v = 1; v < N; v++) {
				double d = dist[u][v];
				double c = maxCap - dist[u][v];
				if (min(c, food[u]) < d - EPS) continue;

				int nn = (int)ceil(food[u]/(c+d) + EPS);
				double res = min(c, food[u]) - d;
				for (int n = nn; n >= 0 && n >= nn-5; n--) {
					if (food[u] - n*(c+d) < d - EPS) continue;
					res = max(res, n*(c-d) + (min(c, food[u] - n*(c+d)) - d));
				}

				if (res < -EPS) continue;
				if (res < 0) res = 0;

				if (res > food[v] + EPS) {
					food[v] = res;
					changed = true;
				}
			}
		}

		if (!changed) return false;
	}
}

int main()
{
	for (int cs = 1; scanf("%d %lf", &N, &maxCap) == 2 && N > 0; cs++) {
		for (int i = 0; i < N; i++)
			scanf("%lf %lf", &X[i], &Y[i]);

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				dist[i][j] = i==j ? 0 : sqrt(sqr(X[i]-X[j]) + sqr(Y[i]-Y[j]));

		int left = 0, right = 1000010;
		while (right - left > 1) {
			int mid = (left + right) / 2;
			if (check(mid))
				right = mid;
			else
				left = mid;
		}

		printf("Trial %d: ", cs);
		assert(right >= 2);
		if (right > 1000000)
			printf("Impossible\n\n");
		else
			printf("%d units of food\n\n", right);
	}
}
