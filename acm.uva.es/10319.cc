// 2-SAT, strongly connected components
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

char adj[128][128];
int S, A;

int inv(int x) {
	return (x < S+A) ? (S+A+x) : (x-S-A);
}

int var(int s1, int a1, int s2, int a2) {
	if (s1 == s2) {
		return (a2 > a1) ? s1 : inv(s1);
	} else if (a1 == a2) {
		return (s1 > s2) ? (S+a1) : inv(S+a1);
	}
	abort();
	return 42;
}

void clause(int x, int y) {
	adj[inv(x)][y] = 1;
	adj[inv(y)][x] = 1;
}

int main()
{
	int T, M, s1, a1, s2, a2;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &S, &A, &M);

		// build implication graph for 2-SAT
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d %d", &s1, &a1, &s2, &a2);
			s1--; a1--; s2--; a2--;
			if (s1 == s2 && a1 == a2) continue;
			if (s1 == s2 || a1 == a2) {
				int x = var(s1, a1, s2, a2);
				clause(x, x);
			} else {
				int x = var(s1,a1, s2,a1), y = var(s2,a1, s2,a2);
				int z = var(s1,a1, s1,a2), w = var(s1,a2, s2,a2);
				// (x&y)|(z&w) = (x|z)&(y|z)&(x|w)&(y|w)
				clause(x, z);
				clause(y, z);
				clause(x, w);
				clause(y, w);
			}
		}

		// formula is satisfiable iff x and inv(x) are not in the same
		// strongly connected component for all x

		int N = 2*(S+A);
		for (int k = 0; k < N; k++) {
			for (int i = 0; i < N; i++) {
				if (adj[i][k] == 0) continue;
				for (int j = 0; j < N; j++) {
					adj[i][j] |= adj[k][j];
				}
			}
		}

		bool res = true;
		for (int x = 0; x < S+A; x++)
			if (adj[x][inv(x)] && adj[inv(x)][x]) res = false;
		printf(res ? "Yes\n" : "No\n");
	}
}
