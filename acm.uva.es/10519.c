#include <stdio.h>
#include <string.h>

int main()
{
	static char s[2048];
	static int a[512], b[512], c[512], n;
	int i, j, k, t;

	while (scanf(" %[0-9]", s) == 1) {
		for (i = 0; s[i] == '0'; i++);

		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(c, 0, sizeof(c));

		for (n = 0; s[i]; n++, i++)
			a[n] = s[i] - '0';

		if (n == 0) {
			printf("1\n");
			continue;
		}

		for (i = 0, j = n - 1; i < j; i++, j--)
			k = a[i], a[i] = a[j], a[j] = k;

		for (i = 0; i < n; i++)
			b[i] = a[i];

		for (i = 0; i < n; i++) {
			if (b[i]-- > 0)
				break;
			else
				b[i] = 9;
		}

		for (i = 0; i < n; i++) {
			for (j = t = 0, k = i; j < n; j++, k++, t /= 10)
				c[k] = (t += c[k] + a[i] * b[j]) % 10;

			for (; t > 0; k++, t /= 10)
				c[k] = (t += c[k]) % 10;
		}

		n = 2 * n + 2;
		for (t = 2, i = 0; t > 0 && i < n; i++, t /= 10)
			c[i] = (t += c[i]) % 10;

		while (n > 1 && c[n - 1] == 0) n--;

		while (n--) putchar(c[n] + '0');
		printf("\n");
	}

	return 0;
}
