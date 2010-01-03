#include <stdio.h>

int cost[64];

int f(int n, int b)
{
	return cost[n%b] + (n >= b ? f(n/b, b) : 0);
}

int main()
{
	int T, Q, cs = 1, q;

	for (scanf("%d", &T); cs <= T; cs++) {
		for (int i = 0; i < 36; i++) scanf("%d", &cost[i]);

		printf("%sCase %d:\n", cs==1?"" : "\n", cs);
		for (scanf("%d", &Q); Q-- > 0 && scanf("%d", &q) == 1;) {
			int best = 0x3fffffff;
			for (int b = 2; b <= 36; b++) best <?= f(q,b);
			printf("Cheapest base(s) for number %d:", q);
			for (int b = 2; b <= 36; b++)
				if (best == f(q,b)) printf(" %d", b);
			printf("\n");
		}
	}
}
