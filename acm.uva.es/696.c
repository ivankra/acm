#include <stdio.h>

int main()
{
	static int k, r, c;
	register int a, b;

	while (scanf("%d%d", &r, &c) == 2 && (r | c) != 0) {
		if (r >= c) {
			a = r;
			b = c;
		} else {
			a = c;
			b = r;
		}

		if (b >= 3)
			k = (a * b + 1) >> 1;
		else if (b == 2)
			k = (((a & 3) >= 2) ? 4 : ((a & 3) << 1)) + (a & ~3);
		else if (b == 1)
			k = a;
		else
			k = 0;

		printf("%d knights may be placed on a %d row %d column board.\n",
		       k, r, c);
	}

	return 0;
}
