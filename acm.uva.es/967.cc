#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char prime[1000010];
int cnt[1000010];

int check(int n) {
	if (n < 2 || n >= 1000000) return 0;

	int t = 1;
	while (t <= n) t *= 10;

	t /= 10;

	for (int m = n;;) {
		if (!prime[m]) return 0;

		m = (m % t) * 10 + (m / t);
		if (m == n) break;
	}

	return 1;
}

int main() {
	memset(prime, 1, sizeof(prime));
	prime[0] = prime[1] = 0;

	for (int i = 2; i <= 1000; i++) {
		if (!prime[i]) continue;
		for (int j = i*i; j <= 1000000; j += i)
			prime[j] = 0;
	}

	cnt[0] = 0;
	for (int n = 1; n <= 1000000; n++)
		cnt[n] = cnt[n-1] + check(n);

	int a, b;
	while (scanf("%d %d", &a, &b) == 2 && a >= 0) {
		if (a > b) swap(a, b);
		int k = cnt[b] - cnt[a-1];
		if (k == 0)
			printf("No Circular Primes.\n");
		else if (k == 1)
			printf("1 Circular Prime.\n");
		else
			printf("%d Circular Primes.\n", k);
	}
}
