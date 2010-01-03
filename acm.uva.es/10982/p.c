#include <stdio.h>
#include <assert.h>
typedef unsigned long long u64;

int nbits(u64 x) {
	int r;
	for (r = 0; x != 0; x &= x-1) r++;
	return r;
}

u64 G[128][2], A[2];
int deg[128], n, m, x, y, T, cs = 1;

int main()
{
	for (scanf("%d", &T); cs <= T && scanf("%d %d", &n, &m) == 2; cs++) {
		int i;

		for (i = 1; i <= n; i++) {
			deg[i] = 0;
			G[i][0] = G[i][1] = 0;
		}

		while (m-- > 0 && scanf("%d %d", &x, &y) == 2) {
			if (y > x) { i = x; x = y; y = i; }
			G[x][y >> 6] |= 1ULL << (y & 63);
			deg[x]++;
		}
		
		A[0] = A[1] = m = 0;
		for (i = 1; i <= n; i++)
			if (2 * (nbits(G[i][0] & A[0]) + nbits(G[i][1] & A[1])) <= deg[i])
				m++, A[i >> 6] |= 1ULL << (i & 63);

		printf("Case #%d: %d\n", cs, m);
		for (i = 1, x = 0; i <= n; i++)
			if (((A[i >> 6] >> (i & 63)) & 1) != 0)
				printf(x++ ? " %d" : "%d", i);
		printf("\n");
	}

	return 0;
}
