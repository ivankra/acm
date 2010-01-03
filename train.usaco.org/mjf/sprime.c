/*
ID: mjf28791
PROG: sprime
LANG: C
*/
#include <stdio.h>

int isprime(int a)
{
	int d, m;

	if (a <= 1 || ((a & 1) == 0 && a != 2))
		return 0;

	/* approximate square root of 'a' */
	for (m = a;; m = d) {
		d = (((a / m) + m) >> 1);
		if (d >= m) break;
	}

	/* trial division */
	for (m += 2, d = 3; d <= m; d += 2)
		if ((a % d) == 0 && d < a) return 0;

	return 1;
}

/* recursive depth-first search. */
void search(int n, int a)
{
	int d, x;

	if (n == 0) {
		printf("%d\n", a);
		return;
	}

	for (d = 1; d <= 9; d++) {
		x = a * 10 + d;
		if (isprime(x))
			search(n - 1, x);
	}
}


int main()
{
	int n;

	freopen("sprime.in", "r", stdin);
	freopen("sprime.out", "w", stdout);

	scanf("%d", &n);

	search(n, 0);

	return 0;
}
