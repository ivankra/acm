/*
ID: infnty1
TASK: twohead
LANG: C++
*/
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> VI;  typedef vector<VI> VVI;

int n, m, p[65536], col[65536], start;
VVI adj;

void upd(int x) {
	int z = x, k = 0;
	while (p[z] != z) { k ^= col[z]; z = p[z]; }
	p[x] = z;
	col[x] = k;
}

int add(int x, int y) {
	if (x < start || y < start) return 0;
	upd(x); upd(y);
	if (p[x] == p[y]) {
		return (col[x] == col[y]) ? 1 : 0;
	} else {
		int t = p[x];
		p[t] = p[y];
		col[t] = col[x] ^ col[y] ^ 1;
		return 0;
	}
}

int main()
{
	freopen("twohead.in", "r", stdin);
	freopen("twohead.out", "w", stdout);

	scanf("%d %d", &n, &m);
	adj = VVI(2*n, VI());
	for (int i = 0; i < m; i++) {
		int x, y; char c, d;
		scanf("%d %c %d %c", &x, &c, &y, &d);
		x = 2*(x-1) + (c=='A'?0:1);
		y = 2*(y-1) + (d=='A'?0:1);
		if (x == y) continue;
		adj[max(x,y)].push_back(min(x,y));
	}

	for (int i = 0; i < 2*n; i++) {
		p[i] = i;
		col[i] = 0;
	}

	int ret = 0;
	for (int s = 0; s < 2*n;) {
		ret++;
		start = s;
		p[s] = s;
		p[s+1] = s+1;
		col[s] = col[s+1] = 0;
		for (s += 2; s < 2*n; s += 2) {
			for (int i = 0; i < (int)adj[s].size(); i++)
				if (add(s, adj[s][i])) goto stop;
			for (int i = 0; i < (int)adj[s+1].size(); i++)
				if (add(s+1, adj[s+1][i])) goto stop;
			if (add(s, s+1)) goto stop;
		}
stop:;
	}

	printf("%d\n", ret);
	return 0;
}
