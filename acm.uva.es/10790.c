#include <stdio.h>

int main()
{
	long long a, b;
	int c;

	for (c = 1; scanf("%lld %lld", &a, &b) == 2 && a != 0; c++)
		printf("Case %d: %lld\n", c, (a * (a - 1) * b * (b - 1)) >> 2);

	return 0;
}
