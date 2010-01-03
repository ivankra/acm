#include <stdio.h>

int main(void)
{
	int n, s, ami, ama, bmi, bma, mmi, mma;
	register int b, m, c;

	scanf("%d", &n);
	for (s = 1; s <= n; s++) {
		scanf("%d %d %d %d %d %d", &ami, &ama, &bmi, &bma, &mmi, &mma);

		c = 0;
		for (b = bmi; b <= bma; b++)
			for (m = mmi; m <= mma; m++)
				if (((b << 1) % m) == 0) c++;

		c = c * (ama - ami + 1);
		printf("Case %d: %d\n", s, c);
	}

	return 0;
}
