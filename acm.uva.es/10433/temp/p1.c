#include <stdio.h>

int a[65536], b[65536], n;

int check()
{
	int i, j, k, c;

	for (i = n - 1; i >= 0 && a[i] == 0; i--);

	if (i < 0 || (i == 0 && a[0] == 1))
		return 0;

	for (i = 0; i < n; i++)
		b[i] = 0;

	for (i = 0; i < n; i++) {
		if (a[i] != 0) {
			for (c = 0, j = 0, k = i; k < n; j++, k++, c /= 10)
				b[k] = (c += b[k] + a[i] * a[j]) % 10;
		}
		if (b[i] != a[i]) return 0;
	}

	return 1;
}

int main()
{
	int i, j, c;

	for (;;) {
		for (n = 0; (c = getchar()) != EOF && c != '\n';)
			if ('0' <= c && c <= '9') a[n++] = c - '0';

		if (n == 0) {
			if (c == EOF) break;
			continue;
		}

		for (i = 0, j = n - 1; i < j;) {
			c = a[i];
			a[i++] = a[j];
			a[j--] = c;
		}

		if (check())
			printf("Automorphic number of %d-digit.\n", n);
		else
			printf("Not an Automorphic number.\n");
	}

	return 0;
}
