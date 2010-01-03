#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;

static ull choose(ull n, ull k)
{
	ull c, i;

	if ((n - k) < k)
		k = n - k;

	if (k == 0) return 1;
	if (k == 1) return n;
	if (k == 2) return ((n * (n - 1)) >> 1);

	for (c = 1, i = 0; i < k; i++)
		c = (c * (n - i)) / (i + 1);

	return c;
}

int main()
{
	static unsigned n, k;

	while (scanf("%u %u", &n, &k) == 2 && (n != 0 || k != 0))
		printf("%u\n", (unsigned)choose(n, k));

	return 0;
}
