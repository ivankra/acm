#include <stdio.h>
#include <string.h>

int main()
{
	int r[32], n, k, s, last, left, q;

	while (scanf("%d %d", &n, &k) == 2 && n > 0) {
		for (s = 0; s < n; s++)
			r[s] = 40;

		for (s = last = 1, left = n, q = 0; left > 0;) {
			while (r[q] <= 0) q = (q + 1) % n;

			if (s >= r[q]) {
				s -= r[q];
				r[q] = 0;
				printf("%3d", q + 1);
				left--;
			} else {
				r[q] -= s;
				s = 0;
			}

			q = (q + 1) % n;

			if (s <= 0)
				s = last = ((last == k) ? 1 : (last + 1));
		}

		printf("\n");
	}

	return 0;
}
