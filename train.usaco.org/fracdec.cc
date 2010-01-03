/*
ID: infnty1
PROB: fracdec
LANG: C++
*/
#include <stdio.h>

int m = 0;

void put(int c)
{
	if (m == 76) { putchar('\n'); m = 0; }
	putchar(c); m++;
}

int main()
{
	int i, j, n, d;

	freopen("fracdec.in", "r", stdin);
	freopen("fracdec.out", "w", stdout);

	scanf("%d %d", &n, &d);

	int *a = new int[d+1];
	char *b = new char[d+10];

	for (i = 0; i < d; i++) a[i] = -1;

	m = printf("%d.", n / d);
	n %= d;

	if (n == 0) { printf("0\n"); return 0; }

	for (j = 0; a[n] < 0; j++) {
		a[n] = j;
		b[j] = (10 * n) / d + '0';
		n = (10 * n) % d;
	}
	b[j] = 0;

	for (i = 0; i < a[n]; i++) put(b[i]);

	if (n != 0) {
		put('(');
		for (; i < j; i++) put(b[i]);
		put(')');
	}
	printf("\n");

	return 0;
}
