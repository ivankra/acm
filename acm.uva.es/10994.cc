#include <stdio.h>
typedef long long i64;

i64 F(i64 n) {
	if (n <= 0) return 0;
	i64 s = 0;
	for (i64 r = 1; r <= 9 && r <= n; r++)
		s += (((n-r)/10)+1) * r;
	return s + F(n/10);
}

int main()
{
	i64 a, b;
	while (scanf("%lld %lld", &a, &b) == 2 && a >= 0)
		printf("%lld\n", F(b) - F(a-1));
	return 0;
}
