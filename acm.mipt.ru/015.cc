#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
	bool operator <(const Point &q) const { return x < q.x; }
};

int main() {
	Point p[200];
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &p[i].x, &p[i].y);
	sort(p, p+n);

	int chk[110];
	memset(chk, 0, sizeof(chk));
	chk[0] = chk[100] = 1;
	for (int i = 0; i < n; i++) chk[p[i].y] = 1;

	int best = 0;
	for (int y1 = 0; y1 < 100; y1++) if (chk[y1]) {
		for (int y2 = y1+1; y2 <= 100; y2++) if (chk[y2]) {
			if (100 * (y2 - y1) <= best) continue;
			int x0 = 0;
			for (int i = 0; i < n; i++) {
				if (p[i].y <= y1 || p[i].y >= y2) continue;
				best >?= (p[i].x - x0) * (y2 - y1);
				x0 = p[i].x;
			}
			best >?= (100 - x0) * (y2 - y1);
		}
	}
	printf("%d\n", best);
}
