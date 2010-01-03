#include <stdio.h>
#include <stdlib.h>

int main()
{
	static int a[65536];
	int i, c, t, n, k;
	long long v, x;
	char buf[128];

	for (;;) {
		for (n = 0;;) {
			while ((c = getchar()) != EOF && c != '\n' &&
			        c != '-' && (c < '0' && c > '9'));
			if (c == EOF || (c == '\n' && n > 0))
				break;
			if (c == '\n' && n == 0)
				continue;
			ungetc(c, stdin);
			scanf("%d", &a[n++]);
		}

		if (n == 0)
			break;

		for (k = 0;;) {
			while ((c = getchar()) != EOF && c != '\n' &&
			        c != '-' && (c < '0' && c > '9'));
			if (c == EOF || (c == '\n' && n > 0))
				break;
			if (c == '\n' && n == 0)
				continue;
			ungetc(c, stdin);
			scanf("%d", &t);

			if (k++ > 0)
				printf(" ");

			x = (long long)t;
			for (v = 0, i = 0; i < n; i++)
				v = v * x + (long long)a[i];

			if (v < 0) {
				printf("-");
				v = -v;
			}

			for (i = 0; i == 0 || v > 0; v /= 10)
				buf[i++] = '0' + (v % 10);

			while (i--)
				putchar(buf[i]);
		}

		printf("\n");
	}

	return 0;
}
