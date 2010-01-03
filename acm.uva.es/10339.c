#include <stdio.h>

int main()
{
	int k, m, a, d;

	while (scanf("%d %d", &k, &m) == 2) {
		d = (k > m) ? (k - m) : (m - k);
		a = ((1440 * (86400 - k) + d) / (2 * d)) % 720;

		printf("%d %d %.2d:%.2d\n",
			k, m, 1 + (((a / 60) + 11) % 12), a % 60);
	}

	return 0;
}
