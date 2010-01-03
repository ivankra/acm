#include <stdio.h>

int main()
{
	int a[3001], b[3001], c[3001], n, m, k, r, x, y, cs=1;
	for (; scanf("%d", &n) == 1 && n > 0; cs++) {
		for (int i = 0; i < n; i++) scanf("%d %d %d", &a[i], &b[i], &c[i]);

		r = 0;
		for (scanf("%d", &m); m-- > 0 && scanf("%d %d", &x, &y) == 2;) {
			k = 0;
			for (int i = 0; i < n; i++)
				if (a[i]*x+b[i]*y+c[i] > 0) k++;
			r += k*(k-1)/2 + (n-k)*(n-k-1)/2;
		}

		printf("Roadmap %d:\n", cs);
		printf("Negative Builders Ltd. will build %d New Roads.\n", r);
	}
}
