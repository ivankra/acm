#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int a, b, t, n;
	register int i, s;

	scanf("%d", &t);
	for (n = 1; n <= t; n++) {
		scanf("%d %d", &a, &b);
		i = (a & 1) ? a : (a + 1);
		for (s = 0; i <= b; i += 2)
			s += i;
		printf("Case %d: %d\n", n, s);
	}

	return 0;
}
