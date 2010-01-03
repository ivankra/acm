#include <stdio.h>

typedef unsigned long u_int32_t;
typedef unsigned long long u_int64_t;

static int modexp(u_int64_t b, u_int32_t e, u_int64_t m)
{
	u_int64_t r;

	for (r = 1; e > 0; e >>= 1) {
		if (e & 1) r = (r * b) % m;
		if (e > 1) b = (b * b) % m;
	}

	return (int)r;
}

static int primep(int n)
{
	static int small[] = {
		3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
		47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
	};
	register int i, j;
	int a, r, s;

	if (n <= 1) return 0;
	if (n <= 3 || n == 5) return 1;
	if ((n & 1) == 0) return 0;

	i = n % 6;
	if (i != 5 && i != 1) return 0;

	/* small primes */
	for (i = 0; i < (sizeof(small) / sizeof(small[0])); i++) {
		if (n == small[i]) return 1;
		if ((n % small[i]) == 0) return 0;
	}

	/* fermat test */
	for (i = 2; i < 8 && i < n; i++)
		if (modexp(i, n - 1, n) != 1) return 0;

	/* rabin-miller test */
	for (s = n - 1, r = 0; (s & 1) == 0; r++, s >>= 1);

	for (a = 1; a <= 9; a++) {
		if (modexp(a, s, n) == 1)
			continue;

		for (j = 0; j < r; j++)
			if (modexp(a, s << j, n) == (n - 1)) break;

		if (j >= r)
			return 0;
	}

	return 1;
}

int main()
{
	static int t, a, b;

	scanf("%d", &t);
	while (t-- > 0 && scanf("%d %d", &a, &b) == 2) {
		if (a > b) { int k = a; a = b; b = k; }

		if (a <= 2) { printf("2\n"); a = 3; }
		if ((a & 1) == 0) a++;

		for (; a <= b; a += 2)
			if (primep(a)) printf("%d\n", a);

		if (t > 0) printf("\n");
	}

	return 0;
}
