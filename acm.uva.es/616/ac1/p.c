#include <stdio.h>

int test(int c, int n)
{
	int i;

	if (c <= 1)
		return 0;

	for (i = 0; i < n; i++)
		if ((c % n) != 1)
			return 0;
		else
			c = ((c - 1) / n) * (n - 1);

	if ((c % n) != 0)
		return 0;

	return 1;
}

int main()
{
	int c, n;

	while (scanf("%d", &c) == 1 && c >= 0) {
		for (n = 10; n >= 1 && !test(c, n); n--);

		if (n < 1)
			printf("%d coconuts, no solution\n", c);
		else
			printf("%d coconuts, %d people and 1 monkey\n", c, n);
	}

	return 0;
}
