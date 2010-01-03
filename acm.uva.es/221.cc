// P.E.
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define EPS 1e-6

struct Building { double x, y, w, d, h; int ok, id; } b[128];

bool operator <(const Building &A, const Building &B) {
	if (fabs(A.x - B.x) >= EPS) return A.x < B.x;
	return A.y < B.y;
}

int main() {
	int N;

	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++) {
			scanf("%lf %lf %lf %lf %lf", &b[i].x, &b[i].y, &b[i].w, &b[i].d, &b[i].h);
			b[i].ok = 0;
			b[i].id = i+1;
		}

		vector<double> xs;
		for (int i = 0; i < N; i++) {
			xs.push_back(b[i].x);
			xs.push_back(b[i].x + b[i].w);
		}
		sort(xs.begin(), xs.end());

		typedef pair<double, int> P;

		for (int i = 0; i+1 < (int)xs.size(); i++) {
			double x1 = xs[i], x2 = xs[i+1];
			if (x2-x1 < EPS) continue;

			vector<P> w;
			for (int j = 0; j < N; j++) {
				if (max(x1,x2) < b[j].x+EPS) continue;
				if (min(x1,x2) > b[j].x+b[j].w-EPS) continue;
				w.push_back(P(b[j].y, j));
			}

			sort(w.begin(), w.end());

			double h = -1;
			for (int k = 0; k < (int)w.size(); k++) {
				int j = w[k].second;
				if (b[j].h > h+EPS) {
					b[j].ok = 1;
					h = b[j].h;
				}
			}
		}

		if (cs > 1) printf("\n");
		printf("For map #%d, the visible buildings are numbered as follows:\n", cs);
		sort(b, b+N);
		for (int i = 0, k = 0; i < N; i++)
			if (b[i].ok) printf(k++ ? " %d" : "%d", b[i].id);
		printf("\n");
	}
}
