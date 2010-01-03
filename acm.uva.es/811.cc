#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define EPS 1e-9

struct Point {
	int x, y, v, l, id;
	bool operator <(const Point &q) const {
		return x<q.x || (x==q.x && y<q.y);
	}
} P[100];
int N;

long long cross(const Point &o, const Point &a, const Point &b) {
	return (a.x-o.x)*(long long)(b.y-o.y)-(a.y-o.y)*(long long)(b.x-o.x);
}

double dist(const Point &p, const Point &q) {
	return sqrt((p.x-q.x)*(double)(p.x-q.x)+(p.y-q.y)*(double)(p.y-q.y));
}

double hull(int sub) {
	Point H[100];
	double res = 0;

	for (int pass = 0; pass < 2; pass++) {
		int m = 0;

		for (int i = 0; i < N; i++) {
			int j = pass ? i : (N-1-i);
			if (sub & (1 << j)) {
				while (m >= 2 && cross(H[m-2], H[m-1], P[j]) <= 0) m--;
				H[m++] = P[j];
			}
		}

		for (int i = 0; i < m-1; i++)
			res += dist(H[i], H[i+1]);
	}

	return res;
}

int main() {
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++) {
			scanf("%d %d %d %d", &P[i].x, &P[i].y, &P[i].v, &P[i].l);
			P[i].id = i+1;
		}
		sort(P, P+N);

		int bestv = 1<<30, best;
		double bestx = 0;

		for (int cut = 0; cut < (1 << N); cut++) {
			int val = 0;
			double wood = 0;
			for (int i = 0; i < N; i++) {
				if (cut & (1 << i)) {
					val += P[i].v;
					wood += P[i].l;
				}
			}

			if (val > bestv) continue;

			wood -= hull(cut ^ ((1 << N) - 1));
			if (wood < -EPS) continue;
			if (wood < EPS) wood = 0.0;

			if (val == bestv && wood > bestx) continue;
			bestv = val;
			bestx = wood;
			best = cut;
		}

		printf("%sForest %d\n", cs==1?"":"\n", cs);
		printf("Cut these trees:");

		int a[100], k=0;
		for (int i = 0; i < N; i++)
			if (best & (1 << i)) a[k++] = P[i].id;
		sort(a, a+k);

		for (int i = 0; i < k; i++) printf(" %d", a[i]);
		printf("\nExtra wood: %.2f\n", bestx);
	}
}
