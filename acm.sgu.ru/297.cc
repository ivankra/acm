#include <stdio.h>

int main()
{
	int n, m, x, a;

	scanf("%d %d", &n, &m);

	x = 0;
	while (m-- > 0 && scanf("%d", &a) == 1)
		x += a;

	printf("%d\n", x % n);

	return 0;
}
