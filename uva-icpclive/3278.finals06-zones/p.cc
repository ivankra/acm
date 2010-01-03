#include <cstdio>

static inline int bitcnt(int x)
{
	int r = 0;
	while (x > 0) {
		x &= x - 1;
		r++;
	}
	return r;
}

int base[256], mask[256], size[256], n, m, need;

int main()
{
	for (int cs = 1; scanf("%d %d", &n, &need) == 2 && n > 0; cs++) {
		for (int i = 0; i < n; i++) scanf("%d", &base[i]);
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			int t, x;
			scanf("%d", &t);
			mask[i] = 0;
			while (t-- > 0 && scanf("%d", &x) == 1)
				mask[i] |= 1 << (x - 1);
			scanf("%d", &size[i]);
		}

		int ret = -1, best = -1;
		for (int w = (1<<n)-1; w >= 0; w--) {
			if (bitcnt(w) != need) continue;

			int c = 0;
			for (int i = 0; i < n; i++)
				if (w & (1 << i)) c += base[i];

			for (int i = 0; i < m; i++)
				if ((w & mask[i]) != 0)
					c -= (bitcnt(w & mask[i]) - 1) * size[i];

			if (c >= best || ret < 0) {
				best = c;
				ret = w;
			}
		}

		if (ret < 0) { ret = best = 0; }

		printf("Case Number %2d\n", cs);
		printf("Number of Customers: %d\n", best);
		printf("Locations recommended:");
		for (int i = 0; i < n; i++)
			if (ret & (1 << i)) printf(" %d", i+1);
		printf("\n\n");
	}
}
