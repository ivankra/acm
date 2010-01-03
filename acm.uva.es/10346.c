#include <stdio.h>

int main()
{
	int n, k, r, b;

	while (scanf("%d %d", &n, &k) == 2) {
		for (r = 0, b = 0; n > 0;) {
			r += n;
			b += n;
			n = b / k;
			b = b % k;
		}

		printf("%d\n", r);
	}

	return 0;
}
