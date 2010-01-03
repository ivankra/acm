#include <cstdio>
#include <cstring>

#define GET(b) ((sieve[(b) >> 5] >> ((b) & 31)) & 1)

int main()
{
	unsigned sieve[16384], out[16384];
	int i, j, k, n;

	memset(sieve, 0, sizeof(sieve));
	for (k = 1;; k++) {
		if (GET(k)) continue;
		i = 2 * k * (k + 1);
		if (i > 500000) break;
		for (j = 2 * k + 1, i = 2 * k * (k + 1); i <= 500000; i += j)
			sieve[i >> 5] |= 1 << (i & 31);
	}

	scanf("%d", &n);
	for (k = 0, i = 2, j = 5; j <= n; i++, j += 2)
		if ((GET(i) | GET(i-1)) == 0) out[k++] = j;

	printf("%d\n", k);
	for (i = 0; i < k; i++)
		printf("2 %u\n", out[i] - 2);

	return 0;
}
