#include <stdio.h>

int main()
{
	static int a[65536];
	int i, k, n, t, x, y;

	for (t = 0; scanf("%d %d", &x, &y) == 2;) {
		printf(t++ ? "\nX = " : "Dear GOD, Pardon Me\nX = ");

		if (x == 1) {
			printf("%d\nK = 1\n", y);
			continue;
		}

		for (a[0] = 1, n = 1; y-- > 0;) {
			for (k = 0, i = 0; i < n; i++, k /= 10)
				a[i] = (k += x * a[i]) % 10;
			if (k) a[n++] = k;
		}

		for (k = 0, y = 0, i = n, a[0] -= (x == 2); i-- > 0; k %= x - 1)
			if ((k = k * 10 + a[i]) >= (x - 1) || y)
				putchar((k / (x - 1)) + '0'), y++;
		a[0] += (x == 2);

		printf("\nK = ");
		while (n-- > 0) putchar(a[n] + '0');
		printf("\n");
	}

	return 0;
}
