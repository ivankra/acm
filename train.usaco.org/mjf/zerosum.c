/*
ID: mjf28791
PROG: zerosum
LANG: C
*/
#include <stdio.h>

int op[16], n;

int iszero()
{
	int r, i, t, x;

	for (i = 1, x = 0;; i++) {
		x = x * 10 + i;
		if (i == n || op[i] > 0) break;
	}

	for (r = x; i < n;) {
		t = op[i++];

		for (x = 0;; i++) {
			x = x * 10 + i;
			if (i == n || op[i] > 0) break;
		}

		if (t == 1)
			r += x;
		else
			r -= x;
	}

	return (r == 0);
}

int main()
{
	int i;

	freopen("zerosum.in", "r", stdin);
	freopen("zerosum.out", "w", stdout);

	scanf("%d", &n);

	for (i = 1; i < n; i++)
		op[i] = 0;

	for (;;) {
		if (iszero()) {
			printf("1");
			for (i = 1; i < n; i++)
				printf("%c%d", " +-"[op[i]], i + 1);
			printf("\n");
		}

		for (i = n - 1; i > 0; i--) {
			if (++op[i] <= 2)
				break;
			op[i] = 0;
		}

		if (i < 1)
			break;
	}

	return 0;
}
