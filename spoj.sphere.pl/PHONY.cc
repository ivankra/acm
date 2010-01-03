#include <cstdio>

unsigned lo, hi, a[501000];
char b[501000], isprime[65536];

#define ref(A,N) A[((N)-lo)>>1]

int main()
{
	for (unsigned i = 0; i < 65536; i++)
		isprime[i] = i>1;

	for (unsigned p = 2; p < 256; p++)
		if (isprime[p])
			for (unsigned q = p * p; q < 65536; q += p)
				isprime[q] = 0;

	while (scanf("%u %u", &lo, &hi) == 2 && lo > 0) {
		if ((lo & 1) == 0) lo++;
		if ((hi & 1) == 0) hi--;
		if (lo > hi) { printf("none\n"); continue; }

		for (unsigned n = lo; n <= hi; n += 2) {
			ref(a, n) = 1;
			ref(b, n) = 0;
		}

		for (unsigned p = 3; p*p <= hi; p += 2) {
			if (!isprime[p]) continue;

			unsigned n = lo - (lo % p);
			while (n < lo || (n & 1) == 0) n += p;

			unsigned m = lo - (lo % (p-1));

			for (; n <= hi; n += p+p) {
				while (m < n-1) m += p-1;
				if (m == n-1) {
					ref(a, n) *= p;
					ref(b, n)++;
					m += p-1;
				} else {
					ref(a, n) = 0;
				}
			}
		}

		int c = 0;
		for (unsigned n = lo; n <= hi; n += 2) {
			if (ref(a, n) == n && ref(b, n) >= 3) {
				printf("%u\n", n);
				c++;
			}
		}
		if (c == 0) printf("none\n");
	}
}


/*
// http://acmicpc-live-archive.uva.es/nuevoportal/data/problem.php?p=2946
//
#include <cstdio>

// The arrays 'a' and 'b' keep temporary values for each odd integer
// in the range [lo, hi].
// Value at index (N-lo)/2 corresponds to the integer N (lo<=N<=hi).

unsigned lo, hi, a[5001000];
char b[5001000], isprime[65536];

#define ref(A,N) A[((N)-lo)>>1]

int main()
{
	for (unsigned i = 0; i < 65536; i++)
		isprime[i] = i>1;

	for (unsigned p = 2; p < 256; p++)
		if (isprime[p])
			for (unsigned q = p * p; q < 65536; q += p)
				isprime[q] = 0;

	for (int cs = 1; scanf("%u %u", &lo, &hi) == 2; cs++) {
		if (cs > 1) printf("\n");

		// Ensure that lo and hi are both odd.
		if ((lo & 1) == 0) lo++;
		if ((hi & 1) == 0) hi--;
		if (lo > hi) { printf("none\n"); continue; }

		for (unsigned n = lo; n <= hi; n += 2) {
			ref(a, n) = 1;
			ref(b, n) = 0;
		}

		// For each prime p in [3, sqrt(hi)]...
		for (unsigned p = 3; p*p <= hi; p += 2) {
			if (!isprime[p]) continue;

			// n = least odd multiple of p in [lo, hi].
			unsigned n = lo - (lo % p);
			while (n < lo || (n & 1) == 0) n += p;

			// m = some multiple of p-1, less than n.
			// (and reasonably close to it.)
			unsigned m = lo - (lo % (p-1));

			// In this loop we look for all numbers n in [lo,hi],
			// divisible by p.  Variable m helps to detect,
			// if n-1 is divisible by p-1.  If so, the value
			// in array a, corresponding to n is multiplied by p
			// (with the goal, that at the end of whole process
			// it'll be equal to n itself, if n is a phony prime).
			// Otherwise the value is set to zero, effectively
			// rendering it as a non-phony.
			// Values in array b helps finding the number of
			// prime factors of n.
			for (; n <= hi; n += p+p) {
				while (m < n-1) m += p-1;
				if (m == n-1) {
					ref(a, n) *= p;
					ref(b, n)++;
					m += p-1;
				} else {
					ref(a, n) = 0;
				}
			}
		}

		// Output.
		int count = 0;
		for (unsigned n = lo; n <= hi; n += 2) {
			if (ref(a, n) == n && ref(b, n) >= 3) {
				printf("%u\n", n);
				count++;
			}
		}
		if (count == 0) printf("none\n");
	}
}
*/
