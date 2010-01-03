#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> E;
typedef vector<E> VE;
typedef vector<int> VI;

struct rec {
	int x, d;
	rec(int x, int d) : x(x), d(d) {}
};
bool operator <(const rec &b, const rec &a) { return a.d < b.d; }

int main()
{
	int T, cs = 1, x, y, c, n, m, dst, src;

	for (scanf("%d", &T), cs = 1; cs <= T; cs++) {
		scanf("%d %d %d %d", &n, &m, &src, &dst);

		vector<VE> G = vector<VE>(n, VE());
		while (m-- > 0 && scanf("%d %d %d", &x, &y, &c) == 3) {
			G[x].push_back(E(y,c));
			G[y].push_back(E(x,c));
		}

		VI dist(n, 0x7fffffff);
		priority_queue<rec> pq;
		pq.push(rec(src, 0));

		while (!pq.empty() && pq.top().x != dst) {
			rec r = pq.top(); pq.pop();
			if (dist[r.x] < r.d) continue;
			dist[r.x] = r.d;
			for (int i = 0; i < G[r.x].size(); i++) {
				int y = G[r.x][i].first;
				if (dist[y] <= dist[r.x] + G[r.x][i].second) continue;
				pq.push(rec(y, dist[y] = dist[r.x] + G[r.x][i].second));
			}
		}

		printf("Case #%d: ", cs);
		if (!pq.empty()) printf("%d\n", dist[dst]);
		else printf("unreachable\n");
	}

	return 0;
}
