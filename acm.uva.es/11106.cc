#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

struct Point {
	int x, y, z;
	bool operator ==(const Point &q) const { return x==q.x && y==q.y; }
};

bool by_xy(const Point &p, const Point &q) { return p.x<q.x || (p.x==q.x && p.y<q.y); }
bool by_yx(const Point &p, const Point &q) { return p.y<q.y || (p.y==q.y && p.x<q.x); }
bool by_xz(const Point &p, const Point &q) { return p.x<q.x || (p.x==q.x && p.z<q.z); }

Point p[100010], q[200010];
int adjx[100010], adjy[100010], N, M;
char seen[100010];

long long solve()
{
	long long res = 0;

	for (int i = 0; i < N; i++)
		p[i].z = i;
		
	sort(p, p+N, by_yx);
	for (int i = 1; i < N; i++)
		if (p[i] == p[i-1]) return -1;

	// do horizontal lines
	M = 0;
	for (int i = 0, j; i < N; i = j) {
		int y = p[i].y;

		// there must be an even number of points with same y
		for (j = i; j < N && p[j].y == y; j++);
		if (((j-i) & 1) != 0) return -1;

		// and an edge between first and second, third and fourth, etc
		for (j = i; p[j].y == y; j += 2) {
			res += p[j+1].x - (long long)p[j].x;
			adjx[p[j].z] = p[j+1].z;
			adjx[p[j+1].z] = p[j].z;

			// events for line sweep
			q[M].x = p[j].x;   q[M].y = y; q[M].z = +1; M++;
			q[M].x = p[j+1].x; q[M].y = y; q[M].z = -1; M++;
		}
	}

	// do vertical lines, and line sweep to detect intersections
	sort(p, p+N, by_xy);

	sort(q, q+M, by_xz);
	set<int> sw;

	for (int i = 0, j, k = 0; i < N; i = j) {
		int x = p[i].x;

		// there must be an even number of points with same y
		for (j = i; j < N && p[j].x == x; j++);
		if (((j-i) & 1) != 0) return -1;

		// process line sweep events
		for (; k < M && q[k].x <= x; k++) {
			if (q[k].x == x && q[k].z > 0) break;

			if (q[k].z > 0)
				sw.insert(q[k].y);
			else
				sw.erase(q[k].y);
		}

		// sw now contains all coordinates y through which horizontal
		// edges pass at current x.

		for (j = i; p[j].x == x; j += 2) {
			res += p[j+1].y - (long long)p[j].y;
			adjy[p[j].z] = p[j+1].z;
			adjy[p[j+1].z] = p[j].z;

			if (sw.upper_bound(p[j].y) != sw.lower_bound(p[j+1].y))
				return -1;    // intersection
		}
	}

	// check connectedness
	memset(seen, 0, sizeof(seen));
	for (int i = 0; !seen[i];) {
		seen[i] = 1;
		i = seen[adjx[i]] ? adjy[i] : adjx[i];
	}

	for (int i = 0; i < N; i++)
		if (!seen[i]) return -1;

	return res;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		for (int i = 0; i < N; i++)
			scanf("%d %d", &p[i].x, &p[i].y);
		printf("%lld\n", solve());
	}
}
