#include <stdio.h>

typedef unsigned long long ull;

static ull choose(ull n, unsigned k)
{
	register ull c;
	register unsigned i;

	if ((n - k) < k)
		k = n - k;

	if (k == 0) return 1;
	if (k == 1) return n;
	if (k == 2) return ((n * (n - 1)) >> 1);

	for (c = 1, i = 0; i < k; i++)
		c = (c * (n - i)) / (ull)(i + 1);

	return c;
}

int main()
{
	static unsigned n, k;

	while (scanf("%u %u", &n, &k) == 2 && (n != 0 || k != 0))
		printf("%u things taken %u at a time is %u exactly.\n",
			n, k, (unsigned)choose(n, k));

	return 0;
}
