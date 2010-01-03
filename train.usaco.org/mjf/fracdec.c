/*
ID: mjf28791
PROG: fracdec
LANG: C
*/
#include <stdio.h>
#include <string.h>

int n;

void put(int c)
{
	if (n++ == 76) {
		putchar('\n');
		n = 1;
	}
	putchar(c);
}

int main()
{
	static int p[131072], s[131072];
	int a, b, i, k;

	freopen("fracdec.in", "r", stdin);
	freopen("fracdec.out", "w", stdout);

	scanf("%d %d", &a, &b);

	memset(p, 0, sizeof(p));

	if ((a % b) == 0) {
		printf("%d.0\n", a / b);
		return 0;
	}

	n = printf("%d.", a / b);
	a %= b;

	for (k = 0; p[a] == 0;) {
		k++;
		p[a] = k;
		s[k] = (a * 10) / b;
		a = (a * 10) % b;
	}

	for (i = 1; i < p[a]; i++)
		put(s[i] + '0');

	if (p[a] != k || s[p[a]] != 0) {
		put('(');
		for (; i <= k; i++)
			put(s[i] + '0');
		put(')');
	}
	putchar('\n');

	return 0;
}
