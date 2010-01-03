#include <cstdio>
#include <cstdlib>

long long phi(long long n) {
	long long res = 1;
	for (long long p = 2; n > 1 && p <= 46340 && p*p <= n; p++) {
		if ((n % p) != 0) continue;

		res *= p - 1;
		n /= p;
		int k = 0;
		while ((n % p) == 0) { k++; res *= p; n /= p; }
	}
	if (n > 1) res *= n-1;
	return res;
}

long long divs(long long n) {
	long long res = 1, d = 2;
	for (; d*d < n; d++)
		if ((n % d) == 0) res+=2;
	if (d*d == n) res++;
	return res;
}

int main() {
	long long n;
	while (scanf("%lld", &n) == 1) {
		if (n <= 2) printf("0\n");
		else printf("%lld\n", n-phi(n) - (divs(n)));
	}
}
