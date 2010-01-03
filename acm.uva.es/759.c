#include <stdio.h>
#include <string.h>

void print(char *s, int n)
{
	static struct {
		char *s;
		int a;
	} tab[] = {
		{ "I", 1 },	{ "IV", 4 },	{ "V", 5 },	{ "IX", 9 },
		{ "X", 10 },	{ "XL", 40 },	{ "L", 50 },	{ "XC", 90 },
		{ "C", 100 },	{ "CD", 400 },	{ "D", 500 },	{ "CM", 900 },
		{ "M", 1000 },	{ NULL, 9999 }
	};
	int k;
	char *p;

	while (n > 0) {
		for (k = 0; tab[k + 1].a <= n; k++);

		for (p = tab[k].s; *p;)
			*s++ = *p++;

		n -= tab[k].a;
	}

	*s = '\0';
}

int main()
{
	static char s[65536], t[4096][32];
	int n;

	for (n = 1; n < 4000; n++)
		print(t[n], n);

	while (gets(s)) {
		for (n = 1; n < 4000 && strcmp(t[n], s) != 0; n++);
		printf((n < 4000) ? "%d\n" : "This is not a valid number\n", n);
	}

	return 0;
}
