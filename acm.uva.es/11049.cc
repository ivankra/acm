#include <cstdio>
#include <cassert>
#include <queue>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	int dist[16][16], prev[16][16], prev_y[16][16], prev_x[16][16];

	int sr, sc, er, ec;
	while (scanf("%d %d %d %d", &sc, &sr, &ec, &er) == 4) {
		int wall[8][8] [8][8];
		memset(wall, 0, sizeof(wall));

		for (int i = 0; i < 3; i++) {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

			if (y1 == y2) {
				if (x1 > x2) swap(x1, x2);
				for (int t = x1+1; t <= x2; t++)
					wall[y1][t] [y1+1][t] = 1;
			} else {
				if (y1 > y2) swap(y1, y2);
				for (int t = y1+1; t <= y2; t++)
					wall[t][x1] [t][x1+1] = 1;
			}
		}

		memset(dist, 0x3f, sizeof(dist));
		dist[sr][sc] = 0;

		queue<int> Q;
		Q.push(sr); Q.push(sc);
		while (!Q.empty()) {
			int y0 = Q.front(); Q.pop();
			int x0 = Q.front(); Q.pop();
//printf("queue: row=%d col=%d  dist=%d\n", y0, x0, dist[y0][x0]);

			if (y0 == er && x0 == ec) break;

			for (int d = 0; d < 4; d++) {
				int dc = "NWES"[d];
				int x1 = x0 + "1021"[d] - '1';
				int y1 = y0 + "0112"[d] - '1';
				if (x1 < 1 || x1 > 6 || y1 < 1 || y1 > 6) continue;
				if (dist[y1][x1] < 100) continue;

				if (wall[y1][x1][y0][x0]) continue;
				if (wall[y0][x0][y1][x1]) continue;

				dist[y1][x1] = dist[y0][x0] + 1;
				prev_y[y1][x1] = y0;
				prev_x[y1][x1] = x0;
				prev[y1][x1] = dc;
				Q.push(y1); Q.push(x1);
			}
		}

		assert(dist[er][ec] < 100);

		string s = "";
		while (sr != er || sc != ec) {
			s = (char)(prev[er][ec]) + s;
			int er1 = prev_y[er][ec];
			ec = prev_x[er][ec];
			er = er1;
		}
		printf("%s\n", s.c_str());
	}
}
