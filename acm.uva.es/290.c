#include <stdio.h>
#include <ctype.h>

int dig[65536], ndig;

void sol(int base)
{
	static int a[65536], b[65536], n, k;
	int i, j;

	for (i = 0, n = ndig; i < n; i++) {
		if ((a[i] = dig[i]) >= base) {
			printf("?");
			return;
		}
	}

	for (k = 0;; k++) {
		for (i = 0, j = n - 1; i < j && a[i] == a[j]; i++, j--);
		if (i >= j) break;

		for (i = 0; i < n; i++)
			b[i] = a[i];

		for (i = 0, j = n - 1; i < n;)
			a[i++] += b[j--];

		for (j = 0, i = 0; i < n; i++, j /= base)
			a[i] = (j += a[i]) % base;

		if (j) a[n++] = j;
	}

	printf("%d", k);
}

int main()
{
	static char s[65536];
	int i;

	while (scanf(" %s", s) == 1) {
		for (i = 0; s[i]; i++) {
			s[i] = toupper(s[i]);
			if (isdigit(s[i]))
				dig[i] = s[i] - '0';
			else if ('A' <= s[i] && s[i] <= 'E')
				dig[i] = s[i] - 'A' + 10;
		}
		ndig = i;

		for (i = 15; i >= 2; i--) {
			sol(i);
			printf((i == 2) ? "\n" : " ");
		}
	}

	return 0;
}
