#include <stdio.h>

int main()
{
	int n;

	while (scanf("%d", &n) == 1 && n >= 0)
		printf("%lld%%\n", (n <= 1) ? 0LL : (25LL * (long long) n));

	return 0;
}
