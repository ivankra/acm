#include <stdio.h>

int main()
{
	int t, r, x, y;

	for (scanf("%d", &t); t-- > 0 && scanf("%d %d", &x, &y) == 2;) {
		r = x % y;
		printf("%d %d\n", y - r, r);
	}

	return 0;
}
