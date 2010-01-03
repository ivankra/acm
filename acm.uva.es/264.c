#include <stdio.h>

static int int_sqrt(int a)
{
	register int x = a, y;

	for (;;) {
		y = (x + (a / x)) >> 1;

		if (y >= x) {
			return x;
		} else {
			x = y;
		}
	}
}

int main(void)
{
	int n, u, v;

	while (scanf("%d", &n) == 1) {
		n--;
		u = (int_sqrt(1 + 8 * n) - 1) >> 1;
		v = n - ((u * (u + 1)) >> 1);

		if (u & 1) 
			printf("TERM %d IS %d/%d\n", n + 1, v + 1, u - v + 1);
		else
			printf("TERM %d IS %d/%d\n", n + 1, u - v + 1, v + 1);
	}
}
