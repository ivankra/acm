#include <stdio.h>

int main()
{
	int x, y, n;
	while (scanf("%d", &n) == 1 && n > 0) {
		for (y = 0; n-- > 0 && scanf("%d", &x) == 1; y ^= x);
		printf(y ? "Yes\n" : "No\n");
	}
	return 0;
}
