#include <stdio.h>
#include <string.h>

int f(int n)
{
	if (n == 1) return 1;
	if (n & 1) { n >>= 1; return 2 * (f(n) % n) + 2; }
	return 2 * f(n >> 1);
}

int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n > 0) printf("%d\n", f(n));
	return 0;
}
