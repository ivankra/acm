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

double X[100], Y[100], M[100];
int N;

double sqr(double x) { return x*x; }
double dist(int i, int j) { return sqrt(sqr(X[i]-X[j]) + sqr(Y[i]-Y[j])); }

int main()
{
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++)
			cin >> X[i] >> Y[i] >> M[i];

		double res = 0, d[100];
		for (int i = 0; i < N; i++) d[i] = dist(0, i);
		d[0] = -1;

		double tm = 0;

		while (true) {
			int u = -1;
			for (int i = 0; i < N; i++)
				if (d[i] >= 0 && (u < 0 || d[i] < d[u])) u = i;
			if (u < 0) break;

			tm = max(tm, d[u]);
			res += tm * M[u];
			d[u] = -1;

			for (int i = 0; i < N; i++)
				if (d[i] >= 0) d[i] = min(d[i], dist(u, i));
		}

		double msum = 0;
		for (int i = 0; i < N; i++)
			msum += M[i];

		res /= msum;

		printf("Island Group: %d  Average %.2lf\n\n", cs, res);
	}
}
