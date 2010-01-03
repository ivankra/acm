#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int N, adj[32][32];
int memo[32], got[32];

int f(int x) {
	if (got[x]++) return memo[x];

	memo[x] = 0;
	for (int y = 0; y < 26; y++)
		if (adj[x][y]) memo[x] += f(y);
	if (memo[x] == 0) memo[x] = 1;

	return memo[x];
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		int M;
		scanf("%d %d", &N, &M);
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < M; i++) {
			char a, b;
			scanf(" %c %c", &a, &b);
			a = toupper(a);
			b = toupper(b);
			adj[a-'A'][b-'A'] = 1;
		}

		memset(got, 0, sizeof(got));
		scanf("%d", &M);

		for (int i = 0; i < M; i++) {
			char path[32];
			scanf(" %s", path);
			for (int j = 0; path[j]; j++) path[j] = toupper(path[j]);

			int res = 1;
			for (int j = 0; path[j] && path[j+1]; j++) {
				for (int k = 'A'; k < path[j+1]; k++)
					if (adj[path[j]-'A'][k-'A']) res += f(k-'A');
			}
			printf("%s: %d\n", path, res);
		}
	}
}
