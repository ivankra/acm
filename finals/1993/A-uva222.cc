#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define EPS 1e-9

int rnd(double x) {
	if (fabs(floor(x)-x) <= fabs(ceil(x)-x)) return (int)floor(x);
	return (int)ceil(x);
}

struct Station {
	double dist, cost;
	bool operator <(const Station b) const { return dist < b.dist; }
};

int main() {
	Station st[64];
	double total, tank, mpg;
	int N;

	for (int cs = 1; scanf("%lf", &total) == 1 && total >= 0; cs++) {
		st[0].dist = 0;
		scanf("%lf %lf %lf %d", &tank, &mpg, &st[0].cost, &N);
		for (int i = 1; i <= N; i++)
			scanf("%lf %lf", &st[i].dist, &st[i].cost);
		sort(st+1, st+N+1);

		int best[64];
		best[N+1] = 0;

		for (int i = N; i >= 0; i--) {
			if (total - st[i].dist < tank*mpg+EPS) {
				best[i] = 200;
				continue;
			}

			best[i] = 1<<30;
			for (int j = N, k = 0; j > i; j--) {
				double d = st[j].dist - st[i].dist;
				if (d < 0 || d > tank*mpg+EPS) continue;
				if (k > 0 && d*2.0 < mpg*tank-EPS) continue;
				best[i] <?= 200 + rnd(st[j].cost*d/mpg) + best[j];
				k++;
			}
		}

		int res = best[0] - 200 + rnd(100*st[0].cost);
		printf("Data Set #%d\n", cs);
		printf("minimum cost = $%d.%.2d\n", res/100, res%100);
	}
}
