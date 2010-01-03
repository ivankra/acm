#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

vector<string> name;

int get() {
	char s[256];
	scanf(" %s", s);
	for (int i = 0; i < (int)name.size(); i++)
		if (name[i] == string(s)) return i;
	name.push_back(s);
	return name.size()-1;
}

int main() {
	int adj[32][32], scc[32], n, m;
	for (int cs = 1; scanf("%d %d", &n, &m) == 2 && n > 0; cs++) {
		name.clear();
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < n; i++) adj[i][i] = 1;
		for (int i = 0; i < m; i++) {
			int x = get();
			int y = get();
			adj[x][y] = 1;
		}

		for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			adj[i][j] |= adj[i][k] & adj[k][j];

		if (cs > 1) printf("\n");
		printf("Calling circles for data set %d:\n", cs);

		memset(scc, 0, sizeof(scc));
		for (int i = 0; i < n; i++) {
			if (scc[i]) continue;

			for (int j = 0, k = 0; j < n; j++) {
				if (adj[i][j] && adj[j][i]) {
					printf(k++ ? ", %s" : "%s",
							name[j].c_str());
					scc[j] = 1;
				}
			}
			printf("\n");
		}
	}
}
