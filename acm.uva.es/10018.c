#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int n, c;
	unsigned long x, y, t;

	scanf("%d", &n);
	while (n-- > 0) {
		scanf("%u", &x);
		for (c = 0; ; c++) {
			t = x;
			for (y = 0; x > 0; x /= 10)
				y = (y * 10) + (x % 10);
			if (y == t)
				break;
			x = y + t;
		}

		printf("%d %u\n", c, y);
	}

	return 0;
}
