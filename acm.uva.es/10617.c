#include <stdio.h>

static char s[256];
static int t, n;
static long long tab[64][64];

static long long f(int a, int b)
{
	long long r;
	int i, j;

	if (a > b) return 0;
	if (a == b) return 1;

	if (tab[a][b] > 0)
		return tab[a][b];

	/* solve recursively */
	r = 1 + f(a + 1, b);
	for (i = b; i > a; i--)
		if (s[i] == s[a]) r += 1 + f(a + 1, i - 1);
	tab[a][b] = r;

	/* find analogous sub-problems in other parts of the string */
	b = b - a + 1;
	for (i = 0; (i + b) <= n; i++) {
		for (j = 0; j < b; j++)
			if (s[i + j] != s[a + j]) break;
		if (j >= b)
			tab[i][i + b - 1] = r;
	}

	return r;
}

int main()
{
	static long long r;
	int c;

	scanf("%d", &t);

	while (t-- > 0) {
		for (n = 0;;) {
			while ((c = getchar()) != EOF && c != '\n')
				if ((c>='A' && c<='Z') || (c>='a' && c<='z'))
					break;

			if (c == EOF || (c == '\n' && n > 0))
				break;

			if (c == '\n')
				continue;

			if (c >= 'A' && c <= 'Z')
				s[n++] = c;
			else
				s[n++] = c - 'a' + 'A';
		}

		if (n == 0)
			break;

		memset(tab, 0, sizeof(tab));
		r = f(0, n - 1);

		for (c = 0; c == 0 || r > 0; r /= 10)
			s[c++] = (r % 10) + '0';

		while (c-- > 0)
			putchar(s[c]);
		putchar('\n');
	}

	return 0;
}
