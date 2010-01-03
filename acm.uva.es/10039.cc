#include <cstdio>
#include <cassert>
#include <string>
#include <map>
#include <vector>
using namespace std;

#define V(c,t) ((c)*1440+(t))
int adj[144*1024], ref[512*1024], next[512*1024], last, n;
void edge(int x, int y) { ref[++last]=y; next[last]=adj[x]; adj[x]=last; }

vector<string> C;
map<string, int> Cn;

int solve(int t0, int x, int y)
{
	static int s[144*1024];
	int a, t, t1, done=0;

	for (t = t0; t < 1440; t++)
		adj[V(x,t)] = -2;

	for (t1 = 0;; t1++) {
		if (t1 >= 1440) return 1;

		t = 1;
		s[0] = adj[V(y,t1)];
		adj[V(y,t1)] = -1;
		done = 0;

		while (t-- > 0) {
			for (a = s[t]; a > 0; a = next[a]) {
				if (adj[ref[a]] == -2) done=1;
				else if (adj[ref[a]] >= 0) s[t++] = adj[ref[a]];
				adj[ref[a]] = -1;
			}
		}

		if (done) break;
	}

	for (t = t0; t < 1440; t++)
		if (adj[V(x,t)] == -1) t0 = t;

	printf("Departure %.4d %s\n", (t0/60)*100+(t0%60), C[x].c_str());
	printf("Arrival   %.4d %s\n", (t1/60)*100+(t1%60), C[y].c_str());
	return 0;
}

int main()
{
	static char buf[65536];
	int i, j, m, nt, T, t=1;

	for (scanf("%d", &T); t <= T && scanf("%d", &n) == 1; t++) {
		printf("Scenario %d\n", t);

		C.clear(); Cn.clear();
		for (i = 0; i < n && scanf(" %s", buf) == 1; i++) {
			C.push_back(buf);
			Cn[buf] = i;
		}

		for (i = 1440*n; i >= 0; i--) adj[i] = 0;
		last = 0;

		for (i = 0; i < n; i++)
			for (j = 1; j < 1440; j++)
				edge(V(i,j), V(i,j-1));

		for (scanf("%d", &nt); nt-- > 0 && scanf("%d", &m) == 1;) {
			int t0, x0, t1, x1;
			for (i = 0; i < m; i++) {
				t0 = t1; x0 = x1;
				scanf("%d %s", &t1, buf); x1 = Cn[buf];
				assert((t1 % 100) < 60 && (t1 / 100) < 24);
				t1 = (t1 / 100) * 60 + (t1 % 100);
				if (i != 0) {
					assert(t0 <= t1);
					edge(V(x1,t1), V(x0,t0));
				}
			}
		}		

		int t0;
		scanf("%d %s", &t0, buf); i = Cn[buf];
		scanf("%s", buf); j = Cn[buf];

		assert((t0 % 100) < 60 && (t0 / 100) < 24);
		t0 = (t0 / 100) * 60 + (t0 % 100);

		assert(i != j);

		if (solve(t0, i, j))
			printf("No connection\n");

		printf("\n");
	}

	return 0;
}
