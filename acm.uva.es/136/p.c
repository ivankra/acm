#include <stdio.h>

int is_ugly(int n)
{
	if (n >= 1 && n < 5) return 1;

	while (n > 1) {
		if ((n & 1) == 0) { n >>= 1; continue; }
		if ((n % 3) == 0) { n /= 3; continue; }
		if ((n % 5) == 0) { n /= 5; continue; }
		return 0;
	}
	return 1;
}

int main()
{
	int i, n;

	for (i = 1, n = 0; i < (1 << 30) && n < 1600; i++)
		if (is_ugly(i)) {
			printf("%u\n", i);
			fflush(stdout);
			n++;
		}

	return 0;
}
