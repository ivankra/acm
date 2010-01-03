/*
ID: infnty1
PROB: picture
LANG: C++
*/
/* O(n^2); sweeping line */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int N;
struct Rect { int x1, y1, x2, y2; } rect[5010];

bool by_y1(const Rect &a, const Rect &b) { return a.y1 < b.y1; }

int solve(int x1, int x2) {
	int U = -0x7fffffff, R = 0;

	for (int i = 0; i < N; i++) {
		Rect &r = rect[i];
		if (max(r.x1, r.x2) <= x1 || min(r.x1, r.x2) >= x2) continue;

		int y1 = 4 * r.y1 - 1;
		int y2 = 4 * r.y2 + 1;

		if (y1 > U) R += 2;
		U >?= y2;
	}

	return R*(x2-x1);
}

int main() {
	freopen("picture.in", "r", stdin);
	freopen("picture.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		Rect &r = rect[i];
		scanf("%d %d %d %d", &r.x1, &r.y1, &r.x2, &r.y2);
	}

	int res = 0;

	for (int t = 0; t < 2; t++) {
		for (int i = 0; i < N; i++) {
			if (rect[i].y1 > rect[i].y2)
				swap(rect[i].y1, rect[i].y2);
		}

		sort(rect, rect+N, by_y1);

		vector<int> xs;
		for (int i = 0; i < N; i++) {
			xs.push_back(rect[i].x1);
			xs.push_back(rect[i].x2);
		}

		sort(xs.begin(), xs.end());
		xs.erase(unique(xs.begin(), xs.end()), xs.end());

		for (int i = 1; i < (int)xs.size(); i++)
			res += solve(xs[i-1], xs[i]);

		for (int i = 0; i < N; i++) {
			Rect &r = rect[i];
			swap(r.x1, r.y1);
			swap(r.x2, r.y2);
		}
	}

	printf("%d\n", res);
}
