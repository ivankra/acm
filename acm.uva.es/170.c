#include <stdio.h>
#include <ctype.h>

int get()
{
	int c;

	while ((c = getchar()) != EOF && c != '#' && !isalnum(c));

	if (c == EOF || c == '#')
		return -1;

	return (toupper(c) | (toupper(getchar()) << 8));
}

int main()
{
	int a[64], p[16], map[256], i, k, u = 0;

	for (i = 0; i < 13; i++)
		map[(int)"A23456789TJQK"[i]] = i;

	for (;;) {
		for (i = 51; i >= 0 && (a[i] = get()) >= 0; i--);

		if (i >= 0)
			break;

		for (i = 0; i < 13; i++)
			p[i] = 4;

		for (k = 0, i = 12; p[i]-- > 0; k++) {
			u = a[i + 13 * p[i]];
			i = map[u & 0xFF];
		}

		printf("%.2d,%c%c\n", k, u & 0xFF, u >> 8);
	}

	return 0;
}
