#include <stdio.h>
typedef long long i64;

int main()
{
	i64 n, m, f, t;
	while (scanf("%lld", &n) == 1 && n >= 0) {
		m = f = 0;
		while (n-- > 0) {
			t = m;
			m += f + 1;
			f = t;
		}
		printf("%lld %lld\n", m, m+f+1);
	}
}
