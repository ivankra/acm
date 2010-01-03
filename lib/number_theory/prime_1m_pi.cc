#include <stdio.h>
#include <string.h>


unsigned primes[80000], nprimes, sieve[163840];
unsigned last[1000001], pi[1000001];

#define GET(b) ((sieve[(b)>>5]>>((b)&31))&1)

void make()
{
	register unsigned i, j, k;
	memset(sieve, 0, sizeof(sieve));
	for (k = 1; k <= 502; k++)
		if (GET(k)==0) for(j=2*k+1,i=2*k*(k+1);i<500001;i+=j) sieve[i>>5]|=1<<(i&31);
	nprimes = 1; primes[0] = 2;
	for (i = 1; i < 500001; i++)
		if (GET(i)==0) primes[nprimes++] = 2*i+1;
	primes[nprimes] = 0;
	for (i = j = 0, k = 0; primes[i]; i++) {
		while (j < primes[i]) { last[j] = k; pi[j++] = i; }
		k = primes[i];
	}
}

int main()
{
	make();
	printf("%d\n", nprimes);

	return 0;
}
