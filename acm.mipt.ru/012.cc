#include <cstdio>
#include <vector>
#include <string>
#include <map>
using namespace std;
typedef vector<int> VI; typedef vector<VI> VVI;

int okay = 1;
map<string, int> id_m;
VVI adj; VI seen;

void dfs(int x) {
	if (seen[x] == 1) return;
	if (seen[x] == 2) { okay = 0; return; }
	seen[x] = 2;
	for (int i = 0; okay && i < (int)adj[x].size(); i++)
		dfs(adj[x][i]);
	seen[x] = 1;
}

int id(const string &s) {
	if (id_m.count(s) == 0) {
		int x = id_m.size();
		return id_m[s] = x;
	}
	return id_m[s];
}

int main() {
	char s[256];
	int n, m;

	scanf("%d", &n);
	adj.assign(21000, VI());
	seen.assign(21000, 0);

	for (int i = 0; okay && i < n; i++) {
		scanf(" %s %d", s, &m);
		int x = id(s);
		if (seen[x]++) okay = 0;
		while (okay && m-- > 0 && scanf(" %s", s) == 1) {
			int y = id(s);
			okay &= (x != y);
			adj[x].push_back(y);
		}
	}

	seen.assign(id_m.size(), 0);
	for (int i = 0; i < (int)id_m.size(); i++) dfs(i);

	printf("%sCORRECT\n", okay ? "" : "NOT ");
}
