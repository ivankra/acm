#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;

int W, H, busy[32][32], dist[32][32][8][8];
struct State {
	int x, y, dx, dy;
	int &d() { return dist[x][y][dx+4][dy+4]; }
} st, en;

int main() {
	int T, M;
	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &W, &H) == 2;) {
		scanf("%d %d", &st.x, &st.y); st.dx = st.dy = 0;
		scanf("%d %d", &en.x, &en.y);

		memset(busy, 0, sizeof(busy));

		scanf("%d", &M);
		while (M-- > 0) {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
			for (int x = x1; x <= x2; x++)
				for (int y = y1; y <= y2; y++)
					busy[x][y] = 1;
		}

		queue<State> Q;
		Q.push(st);

		memset(dist, 0xff, sizeof(dist));
		st.d() = 0;

		while (!Q.empty()) {
			State s = Q.front(); Q.pop();
			if (s.x==en.x && s.y==en.y) {
				printf("Optimal solution takes %d hops.\n", s.d());
				goto done;
			}

			for (int j = -1; j <= 1; j++)
			for (int k = -1; k <= 1; k++) {
				State t;
				t.dx = s.dx + j;
				t.dy = s.dy + k;
				if (abs(t.dx) > 3 || abs(t.dy) > 3) continue;

				t.x = s.x + t.dx;
				t.y = s.y + t.dy;

				if (t.x < 0 || t.x >= W) continue;
				if (t.y < 0 || t.y >= H) continue;
				if (busy[t.x][t.y]) continue;

				if (t.d() >= 0) continue;
				t.d() = s.d() + 1;
				Q.push(t);
			}
		}

		printf("No solution.\n");
done:;
	}
}
