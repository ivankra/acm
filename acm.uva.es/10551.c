#include <stdio.h>
#include <string.h>

int main()
{
	static int x[1024], y[1024], xn, yn, b, s, isdig[256];
	register int i, j, t;

	for (i = 0; i < 256; i++)
		isdig[i] = (i >= '0' && i <= '9');

	while (scanf("%d", &b) == 1 && b != 0) {
		memset(x, '\0', sizeof(x));
		for (i = 0; (t = getchar()) != EOF;) {
			if (isdig[t])
				x[i++] = t - '0';
			else if (i != 0)
				break;
		}
		xn = i;

		for (i = 0, j = xn - 1; i < j;) {
			t = x[i];
			x[i++] = x[j];
			x[j--] = t;
		}

		memset(y, '\0', sizeof(y));
		for (i = 0; (t = getchar()) != EOF;) {
			if (isdig[t])
				y[i++] = t - '0';
			else if (i != 0)
				break;
		}
		yn = i;

		for (i = 0, j = yn - 1; i < j;) {
			t = y[i];
			y[i++] = y[j];
			y[j--] = t;
		}

		for (s = xn - yn; s >= 0;) {
			for (i = s + yn, j = yn; j >= 0; i--, j--)
				if (x[i] != y[j]) break;

			if (j >= 0 && x[i] < y[j]) {
				s--;
				continue;
			}

			for (i = s, j = 0, t = 0; j <= yn; i++, j++) {
				t = x[i] - y[j] - t;

				if (t >= 0) {
					x[i] = t;
					t = 0;
				} else {
					x[i] = t + b;
					t = 1;
				}
			}
		}

		for (i = xn - 1; i > 0 && x[i] == 0; i--);

		while (i >= 0)
			putchar(x[i--] + '0');
		putchar('\n');
	}

	return 0;
}
