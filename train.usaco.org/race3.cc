/*
ID: infnty1
PROB: race3
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

vector< vector<int> > adj;
vector<int> seen;
int N;

bool dfs(int s, int t, int rm) {
	seen.assign(adj.size(), 0);
	vector<int> st(1, s);

	while (st.size() > 0) {
		int x = st.back(); st.pop_back();
		seen[x] = 1;
		if (x == t) return true;

		for (int i = 0; i < (int)adj[x].size(); i++) {
			int y = adj[x][i];
			if (y != rm && !seen[y]) {
				seen[y] = 1;
				st.push_back(y);
			}
		}
	}

	return false;
}

int main()
{
	freopen("race3.in", "r", stdin);
	freopen("race3.out", "w", stdout);

	adj.clear();
	for (;;) {
		vector<int> v;
		int x;
		while (scanf("%d", &x) == 1) {
			if (x == -1) goto stop;
			if (x < 0) break;
			v.push_back(x);
		}
		adj.push_back(v);
	}
stop:	N = adj.size()-1;

	vector<int> res[2];

	for (int x = 1; x < N; x++)
		if (!dfs(0, N, x)) res[0].push_back(x);

	for (int i = 0; i < (int)res[0].size(); i++) {
		int x = res[0][i];

		dfs(0, -1, x);
		vector<int> r0 = seen;

		dfs(x, -1, -1);
		vector<int> rx = seen;

		bool bad = false;
		for (int y = 0; !bad && y <= N; y++)
			if (y != x && r0[y] && rx[y]) bad = true;
		if (!bad) res[1].push_back(x);
	}

	for (int k = 0; k < 2; k++) {
		printf("%d", res[k].size());
		for (int i = 0; i < (int)res[k].size(); i++)
			printf(" %d", res[k][i]);
		printf("\n");
	}

	return 0;
}
