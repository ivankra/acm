#include <stdio.h>

int pwr(int b, int n)
{
	int r, i;

	for (i = 0; (n >> i) > 0; i++);

	for (r = 1; i >= 0; i--) {
		r *= r;

		if ((n >> i) & 1)
			r *= b;
	}

	return r;
}

int main()
{
	int a, b;

	while (scanf("%d %d", &a, &b) == 2)
		printf("%d\n", pwr(a, b));

	return 0;
}
