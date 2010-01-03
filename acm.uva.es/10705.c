#include <stdio.h>

char s[1024], r[1024];
long long n, m;
unsigned long long a, b;
int i, k, t;

int solve()
{
	if (n >= 0) {
		for (m = 0, i = 0; i < k; i++)
			if (s[k - 1 - i] == 'p') m |= 1LL << i;
		if (n > m) return 0;
	}

	if (n < 0) {
		a = -n;
		for (m = 0, i = 0; i < k; i++)
			if (s[k - 1 - i] == 'n') m |= 1LL << i;
		if (a > m) return 0;
	}

	for (r[k] = '\0', i = k - 1; i >= 0; i--) {
		a = (n < 0) ? -n : n;
		b = 1ULL << (k - 1 - i);

		if ((a & b) == 0ULL) {
			r[i] = '0';
		} else {
			r[i] = '1';

			if (s[i] == 'p')
				n -= b;
			else
				n += b;
		}
	}

	return (n == 0);
}

int main()
{
	for (scanf("%d", &t); t-- > 0 && scanf("%d %s %lld", &k, s, &n) == 3;)
		if (solve())
			printf("%s\n", r);
		else
			printf("Impossible\n");

	return 0;
}
