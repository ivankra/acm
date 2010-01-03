#include <cstdio>
#include <deque>
#include <algorithm>
using namespace std;

/* n <= 32, a[i] <= 20 */
int a[64], n, got[641][641], id=42;

struct state {
	int x, y, z;
	state(int x, int y, int z) : x(x), y(y), z(z) {}
};

int solve()
{
	deque<state> q, r;

	sort(a, a+n);

	q.push_back(state(0,0,0));
	for (int i = 0; i < n; i++) {
		for (id++; !q.empty(); q.pop_front()) {
			state s = q.front();
			s.x += a[i];
			if (s.x > s.y) swap(s.x, s.y);
			if (s.y > s.z) swap(s.y, s.z);

			if (got[s.x][s.y] != id) {
				got[s.x][s.y] = id;
				r.push_back(s);
			}
			
			s = q.front();
			s.y += a[i];
			if (s.y > s.z) swap(s.y, s.z);

			if (got[s.x][s.y] != id) {
				got[s.x][s.y] = id;
				r.push_back(s);
			}

			s = q.front();
			s.z += a[i];
			if (got[s.x][s.y] != id) {
				got[s.x][s.y] = id;
				r.push_back(s);
			}
		}
		q.swap(r);
	}

	int best = 0x1fffffff;
	for (; !q.empty(); q.pop_front()) {
		state s = q.front();
		best <?= s.z - s.x;
	}
	return best;
}

int main()
{
	int T, cs=1;

	for (scanf("%d", &T); cs <= T && scanf("%d", &n) == 1; cs++) {
		for (int i = 0; i < n; i++) scanf("%d", &a[i]);
		printf("Case %d: %d\n", cs, solve());
	}

	return 0;
}
