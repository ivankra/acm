#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TNEG	-1
#define TEOL	-2
#define TEOF	-3

struct {
	char *s;
	int n;
} tab[] = {
	{ "negative", TNEG },	{ "zero", 0 },		{ "one", 1 },
	{ "two", 2 },		{ "three", 3 },		{ "four", 4 },
	{ "five", 5 },		{ "six", 6 },		{ "seven", 7 },
	{ "eight", 8 },		{ "nine", 9 },		{ "ten", 10 },
	{ "eleven", 11 },	{ "twelve", 12 },	{ "thirteen", 13 },
	{ "fourteen", 14 },	{ "fifteen", 15 },	{ "sixteen", 16 },
	{ "seventeen", 17 },	{ "eighteen", 18 },	{ "nineteen", 19 },
	{ "twenty", 20 },	{ "thirty", 30 },	{ "forty", 40 },
	{ "fifty", 50 },	{ "sixty", 60 },	{ "seventy", 70 },
	{ "eighty", 80 },	{ "ninety", 90 },	{ "hundred", 100 },
	{ "thousand", 1000 },	{ "million", 1000000 },	{ NULL, 0 }
};

int tok;

int get()
{
	static char buf[1024];
	int i, c;

	while ((c = getchar()) != EOF && c != '\n' && !isalpha(c));

	if (c == '\n')
		return (tok = TEOL);

	if (c == EOF)
		return (tok = TEOF);

	for (i = 0; c != EOF && isalpha(c); c = getchar())
		buf[i++] = tolower(c);
	buf[i] = '\0';

	if (c != EOF)
		ungetc(c, stdin);

	for (i = 0; tab[i].s; i++)
		if (strcmp(tab[i].s, buf) == 0) return (tok = tab[i].n);

	return get();
}

int tens(int *r)
{
	if (tok >= 0 && tok <= 19 && tok != 10) {
		(*r) = tok;
		get();
		return 1;
	} else if (tok >= 10 && tok <= 90) {
		(*r) = tok;
		get();
		if (tok >= 0 && tok <= 9) {
			(*r) += tok;
			get();
		}
		return 1;
	} else {
		(*r) = 0;
		return 0;
	}
}

int hund(int *r)
{
	int n;

	if (tens(r) == 0) {
		if (tok != 100) return 0;
		*r = 1;
	}

	if (tok != 100)
		return 1;

	get();

	tens(&n);
	*r = (*r) * 100 + n;

	return 1;
}


int th(int *r)
{
	int n;

	if (hund(r) == 0) {
		if (tok != 1000) return 0;
		*r = 1;
	}

	if (tok != 1000)
		return 1;

	get();

	hund(&n);
	(*r) = (*r) * 1000 + n;

	return 1;
}

int mln(int *r)
{
	int n;

	if (th(r) == 0) {
		if (tok != 1000000) return 0;
		*r = 1;
	}

	if (tok != 1000000)
		return 1;

	get();

	th(&n);
	(*r) = (*r) * 1000000 + n;

	return 1;
}

int main()
{
	int sign, n;

	for (get(); tok != TEOF;) {
		if (tok == TNEG) {
			sign = -1;
			get();
		} else {
			sign = 1;
		}

		mln(&n);

		printf("%d\n", sign * n);

		while (tok != TEOF && tok != TEOL)
			get();

		if (tok == TEOL)
			get();
	}

	return 0;
}
