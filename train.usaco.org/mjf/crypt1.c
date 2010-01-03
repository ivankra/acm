/*
ID: mjf28791
PROG: crypt1
LANG: C
*/
#include <stdio.h>
#include <string.h>

int s[16];

int f(int n)
{
	if (n == 0)
		return s[0];

	for (; n > 0; n /= 10)
		if (s[n % 10] == 0) return 0;

	return 1;
}

int main()
{
	int n, x, y;

	freopen("crypt1.in", "r", stdin);
	freopen("crypt1.out", "w", stdout);

	memset(s, 0, sizeof(s));
	for (scanf("%d", &n); n-- > 0 && scanf("%d", &x) == 1;)
		s[x] = 1;

	for (n = 0, x = 100; x <= 999; x++) {
		if (!f(x))
			continue;

		for (y = 10; y <= 99 && (x * y) <= 9999; y++)
			if (f(y) && f(x * y) &&
			    ((y % 10) * x) >= 100 && ((y % 10) * x) <= 999 &&
			    ((y / 10) * x) >= 100 && ((y / 10) * x) <= 999 &&
			    f((y % 10) * x) && f((y / 10) * x))
				n++;
	}

	printf("%d\n", n);
	return 0;
}
