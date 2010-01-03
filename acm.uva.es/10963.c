#include <stdio.h>

int main()
{
	int i, d, n, t, x, y;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1; printf(t ? "\n" : "")) {
		if (n < 1) { printf("yes\n"); continue; }

		scanf("%d %d", &x, &y);
		d = x - y;

		for (i = 1; n-- > 1 && scanf("%d %d", &x, &y) == 2;)
			if ((x - y) != d) i = 0;

		printf(i ? "yes\n" : "no\n");
	}

	return 0;
}
