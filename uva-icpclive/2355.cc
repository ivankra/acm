#include <cstdio>
#include <cstring>

int main() {
	int adj[32][32], n, m, p;
	char c1, c2;
	while (scanf("%d %d", &n, &m) == 2 && (n|m) != 0) {
		memset(adj, 0, sizeof(adj));

		p = 0;
		while (++p <= m && scanf(" %c < %c", &c1, &c2) == 2) {
			if (adj[c1-'A'][c2-'A']) continue;

			adj[c1-'A'][c2-'A'] = 1;
			for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				adj[i][j] |= adj[i][k] & adj[k][j];

			for (int i = 0; i < n; i++)
				if (adj[i][i]) {
					printf("Inconsistency found after %d relations.\n", p);
					goto done;
				}

			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (i!=j && adj[i][j]==0 && adj[j][i]==0) goto skip;

			char s[100];
			memset(s, 0, sizeof(s));

			for (int i = 0; i < n; i++) {
				int ls = 0;
				for (int j = 0; j < n; j++)
					if (adj[j][i]) ls++;
				s[ls] = 'A'+i;
			}

			printf("Sorted sequence determined after %d relations: %s.\n", p, s);
			goto done;
skip:;
		}

		printf("Sorted sequence cannot be determined.\n");
done:		while (p++ < m) scanf(" %*c < %*c");
	}
}
