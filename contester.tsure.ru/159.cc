#include <cstdio>
#include <cstring>

int main()
{
	unsigned t, n;
	for (scanf("%u", &t); t-- > 0 && scanf("%u", &n) == 1;) {
		unsigned p;
		for (p = 2; p*p <= n; p++)
			if ((n % p) == 0) break;
		if ((n % p) != 0 || p >= n) { printf("No\n"); continue; }

		n /= p;
		for (p = 2; p*p <= n; p++)
			if ((n % p) == 0) break;
		printf((n>=2 && p*p>n) ? "Yes\n" : "No\n");
	}
}
