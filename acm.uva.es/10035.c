#include <stdio.h>

int main()
{
	unsigned a, b, c;
	int n;

	while (scanf("%u %u", &a, &b) > 0 && (a != 0 || b != 0)) {
		for (n = 0, c = 0; a != 0 || b != 0; a /= 10, b /= 10) {
			c = (c + (a % 10) + (b % 10)) / 10;
			if (c != 0)
				n++;
		}

		if (n == 0)
			printf("No carry operation.\n");
		else
			printf("%d carry operation%s.\n", n, n == 1 ? "" : "s");
	}

	return 0;
}
