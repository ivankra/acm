#include <stdio.h>
#include <string.h>

char dig[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main()
{
	static int tab[256], m[64], r;
	int i, c;

	for (i = 0; i < 256; i++)
		tab[i] = -1;

	for (i = 0; dig[i]; i++)
		tab[(int)dig[i]] = i;

	for (;;) {
		for (i = 2; i <= 62; i++)
			m[i] = 0;

		if ((c = getchar()) == EOF)
			break;

		for (r = 2; c != '\n' && c != EOF; c = getchar()) {
			if ((c = tab[c]) < 0)
				continue;

			if (c >= r)
				r = c + 1;

			for (i = r; i <= 62; i++)
				m[i] = (m[i] * i + c) % (i - 1);
		}

		for (; r <= 62; r++)
			if (m[r] == 0) break;

		printf((r <= 62) ? "%d\n" : "such number is impossible!\n", r);
	}

	return 0;
}
