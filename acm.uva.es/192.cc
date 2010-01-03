#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

struct Node {
	int d, s;
	vector<int> out;
};

vector<Node> node;
vector<int> ts, seen, memo;
int N;

int dfs(int x) {
	if (seen[x] < 0) return 1;
	if (seen[x] > 0) return 0;
	if (node[x].s) { seen[x] = 1; return 0; }

	seen[x] = -1;
	for (int i = 0; i < (int)node[x].out.size(); i++) {
		int y = node[x].out[i];
		if (dfs(y)) return 1;
	}

	seen[x] = 1;
	ts.push_back(x);
	return 0;
}

int main() {
	int T, M, x, y, clo;
	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &clo, &N) == 2;) {
		node.clear();
		for (int i = 0; i < N; i++) {
			char c;
			Node n;
			int t = scanf(" %c %d", &c, &n.d);
			assert(t == 2);
			n.s = (c != 'a');
			n.out.clear();
			node.push_back(n);
		}

		int t = scanf("%d", &M);
		assert(t == 1);
		while (M-- > 0 && scanf("%d %d", &x, &y) == 2) {
			assert(0 <= x && x < N);
			assert(0 <= y && y < N);
			node[x].out.push_back(y);
		}

		ts.clear();
		seen.assign(N, 0);

		int cyc = 0;
		for (int i = 0; i < N; i++) {
			if (seen[i] == 0 && !node[i].s && dfs(i)) {
				printf("Circuit contains cycle.\n");
				cyc = 1;
				break;
			}
		}
		if (cyc) continue;

		memo.assign(N, 0);
		for (int i = 0; i < (int)ts.size(); i++) {
			int x = ts[i];
			for (int j = 0; j < (int)node[x].out.size(); j++) {
				int y = node[x].out[j];
				memo[x] >?= node[x].d + memo[y];
			}
		}

		int best = 0;
		for (int x = 0; x < N; x++) {
			if (!node[x].s) continue;
			for (int j = 0; j < (int)node[x].out.size(); j++) {
				int y = node[x].out[j];
				if (!node[y].s) best >?= memo[y];
			}
		}

		if (best > clo)
			printf("Clock period exceeded.\n");
		else
			printf("Synchronous design. Maximum delay: %d.\n", best);
	}
}
