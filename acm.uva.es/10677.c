#include <stdio.h>

int main()
{
	int a[16], b1, b2, r1, r2, t, i, j;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d %d %d", &b1, &b2, &r1, &r2) == 4;) {
		for (r2--; r2 > r1; r2--) {
			for (i = r2, j = 0; i > 0; i /= b1)
				a[j++] = i % b1;
			for (i = 0; j-- > 0;)
				i = i * b2 + a[j];
			if ((i % r2) == 0) break;
		}
		printf((r2 > r1) ? "%d\n" : "Non-existent.\n", r2);
	}

	return 0;
}
