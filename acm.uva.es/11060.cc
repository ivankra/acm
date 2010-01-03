#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;

map<string, int> nmap;
vector<string> name;

int adj[128][128], indeg[128], seen[128];
int N;

int main() {
	int M;
	char s[1000], t[1000];

	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		nmap.clear();
		name.clear();

		for (int i = 0; i < N; i++) {
			scanf(" %s", s);
			name.push_back(s);
			nmap[s] = i;
		}

		memset(adj, 0, sizeof(adj));
		memset(indeg, 0, sizeof(indeg));

		scanf("%d", &M);
		while (M-- > 0 && scanf(" %s %s", s, t) == 2) {
			int x = nmap[s];
			int y = nmap[t];
			if (x!=y && adj[x][y]==0) {
				adj[x][y] = 1;
				indeg[y]++;
			}
		}

		printf("Case #%d: Dilbert should drink beverages in this order:", cs);

		memset(seen, 0, sizeof(seen));
		for (;;) {
			int x;

			for (x = 0; x < N; x++) {
				if (!seen[x] && indeg[x] == 0) break;
			}
			if (x >= N) break;

			printf(" %s", name[x].c_str());

			seen[x] = 1;
			for (int y = 0; y < N; y++)
				if (adj[x][y]) { indeg[y]--; adj[x][y]=0; }
		}
		printf(".\n\n");
	}

	return 0;
}
