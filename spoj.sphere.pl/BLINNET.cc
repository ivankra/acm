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
using namespace std;
typedef long long LL;
const double PI = 2 * acos(0.0);

struct Edge {
	int x, y;
	long long c;

	bool operator <(const Edge &e) const {
		return c < e.c;
	}
};

int p[10001];

int f(int x) {
	if (p[p[x]] != p[x])
		p[x] = f(p[x]);
	return p[x];
}

int main()
{
	int T, N, deg;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);

		vector<Edge> E;
		Edge e;
		for (e.x = 1; e.x <= N; e.x++) {
			scanf(" %*s %d", &deg);
			for (int j = 0; j < deg; j++) {
				scanf("%d %lld", &e.y, &e.c);
				E.push_back(e);
			}
		}

		sort(E.begin(), E.end());

		for (int i = 1; i <= N; i++)
			p[i] = i;

		long long res = 0;
		for (int i = 0; i < (int)E.size(); i++) {
			int x = f(E[i].x);
			int y = f(E[i].y);
			if (x == y) continue;
			p[x] = y;
			res += E[i].c;
		}
		printf("%lld\n", res);
	}
}
