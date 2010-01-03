/*
TASK: sightsee
LANG: C++
ID: infnty1
*/
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

int N, M, Fun[1001];
struct { int a, b, t; } edge[5000];

double dist[1001];

// Checks if there's a tour with average fun value per time of at least q.
bool check(double q)
{
	for (int i = 1; i <= N; i++)
		dist[i] = 0;

	for (int iter = 0; ; iter++) {
		if (iter > 3*N)
			return true;

		bool changed = false;

		for (int j = 0; j < M; j++) {
			int x = edge[j].a;
			int y = edge[j].b;
			double c = edge[j].t * q - Fun[y];
			if (dist[x] + c + 1e-9 < dist[y]) {
				dist[y] = dist[x] + c;
				changed = true;
			}
		}

		if (!changed) {
			return false;
		}
	}
}

int main()
{
	assert(freopen("sightsee.in", "r", stdin) != NULL);
	assert(freopen("sightsee.out", "w", stdout) != NULL);

	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &Fun[i]);

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &edge[i].a, &edge[i].b, &edge[i].t);
	}

	double left = 0, right = 1000;
	for (int k = 0; k < 30; k++) {
		double mid = (left + right) / 2;
		if (check(mid))
			left = mid;
		else
			right = mid;
	}
	printf("%.2lf\n", (left + right) / 2);
}
