#include <stdio.h>
#include <string.h>
#include <ctype.h>

int map[256];

int check(char *s)
{
	static int a[64];
	int p, q, r;

	memset(a, 0, sizeof(a));
	for (r = 0, p = 12; a[p] < 4; r++) {
#if 1
		q = map[s[4 * p + a[p]]];
#else
		q = map[s[p + 13 * a[p]]];
#endif

		a[p]++;
		p = q;
	}

	return (r == 52);
}

int main()
{
	static char s[1024];
	int i, c;

	for (i = 1; i <= 9; i++)
		map[i + '0'] = i - 1;
	map['J'] = 0;
	map['T'] = 9;
	map['A'] = 10;
	map['Q'] = 11;
	map['K'] = 12;

	for (;;) {
		for (i = 0; i < 52 && (c = getchar()) != EOF && c != '0';)
			if (isalnum(c)) s[i++] = toupper(c);
		if (i < 52) break;

		for (i = 0; i < 52; i++)
			s[52 + i] = s[i];

		for (c = 0, i = 0; i < 52; i++)
			c += check(s + i);

		printf("%d\n", c);
	}

	return 0;
}
