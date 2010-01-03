// Euler path/tour
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

vector<string> out, adj[26];

void euler(int s) {
	while (adj[s].size() > 0) {
		string e = adj[s].back();
		adj[s].pop_back();
		euler(e[e.size()-1]-'a');
		out.push_back(e);
	}
}

int main() {
	int N, T, deg[32];
	scanf("%d", &T);

	while (T-- > 0 && scanf("%d", &N) == 1) {
		for (int i = 0; i < 26; i++) {
			adj[i].clear();
			deg[i] = 0;
		}

		for (int i = 0; i < N; i++) {
			char s[100];
			scanf(" %s", s);
			int x = s[0] - 'a';
			int y = s[strlen(s)-1] - 'a';
			adj[x].push_back(string(s));
			deg[x]++;
			deg[y]--;
		}

		for (int i = 0; i < 26; i++) {
			sort(adj[i].begin(), adj[i].end());
			reverse(adj[i].begin(), adj[i].end());
		}

		int s, ns=0, t, nt=0;
		for (int i = 0; i < 26; i++) {
			if (deg[i] == 0) continue;
			else if (deg[i] == 1) { s = i; ns++; }
			else if (deg[i] == -1) { t = i; nt++; }
			else goto no;
		}

		out.clear();
		if (ns == 1 && nt == 1) {
			euler(s);
		} else if (ns == 0 && nt == 0) {
			for (int i = 0; i < 26; i++)
				if (adj[i].size() != 0) { euler(i); break; }
		} else {
			goto no;
		}

		if (out.size() != N) goto no;

		for (int i = (int)out.size()-1; i >= 0; i--)
			printf(i?"%s.":"%s\n", out[i].c_str());
		
		continue;

no:		printf("***\n");
	}
}
