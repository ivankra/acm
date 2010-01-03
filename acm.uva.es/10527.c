#include <stdio.h>
#include <ctype.h>

int div(int a[], int n, int d)
{
	int i, m, r, q;

	for (r = 0, m = 0, i = 0; i < n; i++) {
		r = r * 10 + a[i];
		q = r / d;
		r %= d;
		if (m > 0 || q > 0) a[m++] = q;
	}

	if (r != 0) return -1;

	return m;
}

int main()
{
	static char s[65536];
	static int a[65536], p[10];
	int i, j, n;

	while (scanf("%s", s) >= 1 && s[0] != '-') {
		for (a[0] = 0, i = n = 0; s[i]; i++)
			if (isdigit(s[i]) && (n > 0 || s[i] != '0'))
				a[n++] = s[i] - '0';

		if (n <= 1) {
			printf("%d\n", 10 + a[0]);
			continue;
		}

		for (i = 0; i < 10; i++)
			p[i] = 0;

		while (a[n - 1] == 0)
			p[2]++, p[5]++, n--;

		while ((a[n - 1] % 5) == 0) {
			p[5]++;
			n = div(a, n, 5);
		}

		while ((a[n - 1] % 2) == 0) {
			p[2]++;
			n = div(a, n, 2);
		}

		for (;;) {
			for (j = 0, i = 0; i < n; i++)
				j += a[i];
			if ((j % 3) != 0) break;
			p[3]++;
			n = div(a, n, 3);
		}

		while (n > 1 || (n == 1 && a[0] != 1)) {
			n = div(a, n, 7);
			p[7]++;
		}

		if (n < 0) {
			printf("There is no such number.\n");
			continue;
		}

		i = 0;
		while (p[3] >= 2) s[i++] = '9', p[3] -= 2;
		while (p[2] >= 3) s[i++] = '8', p[2] -= 3;
		while (p[7] >= 1) s[i++] = '7', p[7]--;
		while (p[2] >= 1 && p[3] >= 1) s[i++] = '6', p[2]--, p[3]--;
		while (p[5] >= 1) s[i++] = '5', p[5]--;
		while (p[2] >= 2) s[i++] = '4', p[2] -= 2;
		while (p[3] >= 1) s[i++] = '3', p[3]--;
		while (p[2] >= 1) s[i++] = '2', p[2]--;

		while (i-- > 0)
			putchar(s[i]);
		printf("\n");
	}

	return 0;
}
