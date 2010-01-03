#include <stdio.h>
#define MAXLEN 1000100

int main(void)
{
	static char a[MAXLEN], b[MAXLEN];
	static int t, n;
	int i, c, m;

	scanf("%d", &n);
	while (n-- > 0) {
		scanf("%d", &m);
		for (i = 0; i < m; i++) {
			scanf("%d", &t);
			a[i] = t;
			scanf("%d", &t);
			b[i] = t;
		}

		for (i = m - 1, c = 0; i >= 0; i--) {
			c += a[i] + b[i];
			a[i] = '0' + (c % 10);
			c /= 10;
		}

		fwrite(a, 1, m, stdout);
		putchar('\n');

		if (n != 0) putchar('\n');
	}

	return 0;
}
