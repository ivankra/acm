#include <stdio.h>

int write(int, char *, int);

#define MAXN 204

int main(void)
{
	int i, m, n, c;
	char x[MAXN], y[MAXN], z[MAXN];

	scanf("%d\n", &n);
	while (n-- > 0) {
		while ((c = getchar()) != EOF && (c < '0' || c > '9'));
		for (i = 0;;) {
			if (i < MAXN)
				x[i++] = c - '0';
			c = getchar();
			if (c == EOF || (c < '0' || c > '9')) break;
		}
		m = i;
		while (i < MAXN)
			x[i++] = 0;

		while ((c = getchar()) != EOF && (c < '0' || c > '9'));
		for (i = 0;;) {
			if (i < MAXN)
				y[i++] = c - '0';
			c = getchar();
			if (c == EOF || (c < '0' || c > '9')) break;
		}
		if (m < i) m = i;
		while (i < MAXN)
			y[i++] = 0;

		for (c = 0, m++, i = 0; i < m || c; i++) {
			c += x[i] + y[i];
			z[i] = '0' + (c % 10);
			c /= 10;
		}

		for (m = i - 1; z[m] == '0' && m > 0; m--);
		z[++m] = '\n';
		for (i = 0; z[i] == '0' && i <= m; i++);
		if (i >= m) {
			write(1, "0\n", 2);
		} else {
			write(1, z+i, m-i+1);
		}
	}

	return 0;
}
