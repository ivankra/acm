#include <stdio.h>
typedef long long i64;

int main()
{
	i64 Vt, V0;
	while (scanf("%lld %lld", &Vt, &V0) == 2 && Vt > 0 && V0 > 0) {
		i64 ret = 0, best = 0;
		for (i64 n = 1; Vt > n*V0; n++) {
			i64 x = n*(Vt-n*V0);
			if (x == best) {
				ret = 0;
			} else if (x > best) {
				ret = n;
				best = x;
			}
		}
		printf("%lld\n", ret);
	}
}
