#include <stdio.h>

int main()
{
	static int t, n, a, b, c, r;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (r = 0; n-- > 0 && scanf("%d%d%d", &a, &b, &c) == 3;)
			r += a * c;
		printf("%d\n", r);
	}

	return 0;
}
