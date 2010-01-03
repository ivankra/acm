#include <cstdio>

int main()
{
	int i, m, k;
	long long r;
	scanf("%d %d", &m, &k);
	for (r = 1, i = 1; i < k; i++)
		r = (r * (long long)(m + k - i)) / (long long)i;
	printf("%lld\n", r);
	return 0;
}
