#include <stdio.h>

int main()
{
	unsigned i, n, r, t, T;
	for (scanf("%u", &T); T-- > 0 && scanf("%u %u", &t, &n) == 2;) {
		for (r = 0, i = 1; i*i<n; i++) {
			if ((n % i) != 0) continue;
			r += (i&1) + ((n/i)&1);
		}
		if (i*i==n) r+=i&1;
		printf("%u %u\n", t, r-1);
	}

	return 0;
}
