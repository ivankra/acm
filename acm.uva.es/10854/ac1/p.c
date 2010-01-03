#include <stdio.h>
#include <string.h>

char kw[1024];

void next()
{
	if (scanf(" %s", kw) != 1)
		kw[0] = 'E';
	kw[0] &= ~0x20;
}

long long solve()
{
	long long r, s;

	for (r = 1;;) {
		if (kw[0] == 'I') {
			next();
			s = solve();
			next();
			r *= (s + solve());
			next();
		} else if (kw[0] == 'S') {
			next();
		} else {
			return r;
		}
	}
}

int main()
{
	int t;

	for (scanf("%d", &t); t-- > 0;) {
		next();
		printf("%lld\n", solve());
	}

	return 0;
}
