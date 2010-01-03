#include <stdio.h>
#include <string.h>
#include <assert.h>

int P[664580];

#define GET(b) ((sieve[(b) >> 5] >> ((b) & 31)) & 1)
#define ISPRIME(p) (p == 2 || (p > 2 && (p & 1) != 0 && (GET((p - 1) >> 1) == 0)))

void make()
{
	static unsigned sieve[320000];
	register int i, j, k;

	memset(sieve, 0, sizeof(sieve));
	for (k = 1; k < 1581; k++) {
		if (GET(k)) continue;
		for (j = 2 * k + 1, i = 2 * k * (k + 1); i < 5000000; i += j)
			sieve[i >> 5] |= 1 << (i & 31);
	}

	j = 1;
	P[0] = 2;

	for (i = 1; i < 5000000; i++)
		if (GET(i) == 0) P[j++] = 2 * i + 1;
	P[j] = 0;
}

static void sort(int a[], int n)
{
	int i, j, p, t;

re:	if (n < 12) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	for (i = 0, j = n - 1, p = a[n >> 1];;) {
		while (a[i] < p) i++;
		while (a[j] > p) j--;

		if (i >= j)
			break;

		t = a[i];
		a[i++] = a[j];
		a[j--] = t;
	}

	if ((n - i) > 1)
		sort(a + i, n - i);

	n = i;
	goto re;
}

/* sigma(2^n * p) = (2^(n+1) - 1)(p + 1); p prime */
int sigma(int x)
{
	int n;
	for (n = 0; (x & 1) == 0; n++, x >>= 1);
	return ((1 << (n + 1)) - 1) * (x + 1);
}

int X[1401659+1024];
long long S[1401659+1024];

int main()
{
	int i, j, c, k, n;

	make();

	for (k = 0, i = 1; P[i]; i++)
		for (j = P[i] << 1; j <= 10000000; j <<= 1)
			X[k++] = j;

	sort(X, k);

	S[0] = sigma(X[0]) - 2 * X[0];
	for (i = 1; i < k; i++)
		S[i] = S[i - 1] + sigma(X[i]) - 2 * X[i];

#if 0
printf("k=%d\n", k);
printf("s = %lld\n", S[k-1]);

	for (i = 0; i < 20; i++)
		printf("%d[%d:s=%lld] ", X[i], sigma(X[i]) - 2 * X[i], S[i]);
	printf("\n");
#endif

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0, j = k - 1; i < j;) {
			c = (i + j + 1) >> 1;
			if (X[c] < n)
				i = c;
			else if (X[c] > n)
				j = c - 1;
			else
				i = j = c;
		}
		while ((i + 1) < k && X[i + 1] < n) i++;

		printf("%d %lld\n", n, S[i]);
	}

	return 0;
}
