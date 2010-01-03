#include <stdio.h>
#include <string.h>

int read(int, char *, int);

int seq[16384], primes[8192], n;
unsigned sieve[8192];

int is_prime(int a)
{
	int i;

	if (a < 65536)
		return (((sieve[a >> 5] >> (a & 31)) & 1) ^ 1);

	for (i = 0; i < 448; i++)
		if ((a % primes[i]) == 0) return 0;

	return 1;
}

void make_sieve()
{
	int i, j;

	memset(sieve, 0, sizeof(sieve));
	sieve[0] = 3;

	for (i = 2; i < 256; i++) {
		if ((sieve[i >> 5] >> (i & 31)) & 1) continue;
		for (j = i * i; j < 65536; j += i)
			sieve[j >> 5] |= 1 << (j & 31);
	}

	for (i = j = 0;; i++) {
		if (((sieve[i >> 5] >> (i & 31)) & 1) == 0) {
			primes[j++] = i;
			if (j > 512) break;
		}
	}
}

void solve()
{
	int i, k, f, s;

	for (f = seq[1], k = 2; k <= n; f += seq[k++]) {
		for (i = k, s = f; i <= n; i++) {
			s += seq[i] - seq[i - k];
			if (!is_prime(s)) continue;

			printf("Shortest primed subsequence is length %d:", k);
			for (i -= k - 1; k-- > 0; i++)
				printf(" %d", seq[i]);
			printf("\n");
			return;
		}
	}

	printf("This sequence is anti-primed.\n");
}

int main()
{
	static char inbuf[1048576];
	static int isdig[256], t;
	char *inp;
	int i, j;

	make_sieve();

	memset(isdig, 0, sizeof(isdig));
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

#define READ(x) \
	{ while (!isdig[*inp]) inp++; \
	  for (x = *inp++ - '0'; isdig[*inp];) x = x * 10 + *inp++ - '0'; }

	READ(t);

	while (t-- > 0) {
		READ(n);

		seq[0] = 0;
		for (i = 1; i <= n; i++) {
			READ(j);
			seq[i] = j;
		}

		solve();
	}

	return 0;
}
