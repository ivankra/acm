#include <stdio.h>

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int get(int a, int b, int c)
{
	return (2 * a * b + 2 * a * c + 2 * b * c);
}

int main()
{
	int a, b, n, m, r, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (r = get(1, 1, n), a = 2; a <= n; a++) {
			if ((n % a) != 0) continue;
			for (m = n / a, b = 1; b <= m; b++)
				if ((m % b) == 0) r = min(r, get(a, b, m / b));
		}

		printf("%d\n", r);
	}

	return 0;
}
