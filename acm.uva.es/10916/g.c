#include <stdio.h>
#include <math.h>

int main()
{
	int y, w, b, n;

	for (y = 1940, w = 1, b = 0; y <= 2160; y += 10, w *= 2, b++) {
		for (n = 1;; n++)
			if ((lgamma(n + 2.) / log(2.)) > (double)w) break;

		printf("y=%d w=2^%d=%d n=%d\n", y, b, w, n);
	}

	return 0;
}
