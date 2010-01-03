#include <stdio.h>

long long len, amin, amax, bmin, bmax;

char *solve()
{
	long long d, q;

	if (len <= amax)
		return "A";

	d = amax - amin + bmin - bmax;
	q = (len - 1) / (amin + bmax);

	if (d < 0 && q > ((bmax - bmin - amax + d + 1) / d))
		return "B";

	return (((len - 1) % (amin + bmax)) < (amax + q * d)) ? "A" : "B";
}

int main()
{
	int t;

	for (scanf("%d", &t); t-- > 0;) {
		scanf("%lld %lld %lld %lld %lld", &len, &amin, &amax, &bmin, &bmax);
		printf("%s\n", solve());
	}

	return 0;
}
