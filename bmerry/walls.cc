#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

static int dx[] = { 1, -1, 0, 0 };
static int dy[] = { 0, 0, 1, -1 };

int width, height;
int maze[1024][1024];
int prev[1000001];
long long dist[1000001];

struct Cmp {
	bool operator()(int i, int j) const {
		return (dist[i] != dist[j]) ? (dist[i] < dist[j]) : (i < j);
	}
};

int main()
{
	freopen("walls.in", "r", stdin);
	freopen("walls.out", "w", stdout);

	scanf("%d %d", &width, &height);

	int SX, SY, EX, EY;
	scanf("%d %d %d %d", &SX, &SY, &EX, &EY);
	--SX; --SY; --EX; --EY;

	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
			scanf("%d", &maze[y][x]);

	int src = SY*width + SX;
	int dst = EY*width + EX;

	memset(dist, 0x3f, sizeof(dist));
	dist[src] = 0;

	set<int, Cmp> Q;
	Q.insert(src);

	while (!Q.empty()) {
		int u = *Q.begin();
		if (u == dst) break;

		Q.erase(Q.begin());

		int y1 = u / width;
		int x1 = u % width;

		for (int dir = 0; dir < 4; dir++) {
			int y2 = y1 + dy[dir];
			int x2 = x1 + dx[dir];
			if (y2 < 0 || y2 >= height || x2 < 0 || x2 >= width) continue;

			int v = y2 * width + x2;
			long long d = dist[u] + 1 + (maze[y2][x2] == 0 ? 0 : 10000000);
			if (d < dist[v]) {
				Q.erase(v);
				dist[v] = d;
				prev[v] = u;
				Q.insert(v);
			}
		}
	}

	long long d = dist[dst];
	printf("%lld %lld\n", d / 10000000, d % 10000000);

	vector<int> path;
	for (int u = dst; u != src; u = prev[u])
		path.push_back(u);
	path.push_back(src);

	for (int i = path.size()-1; i >= 0; i--) {
		printf("%d %d\n", path[i]%width+1, path[i]/width+1);
	}

	fflush(stdout);
	return 0;
}
