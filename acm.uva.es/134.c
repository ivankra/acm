#include <stdio.h>
#include <string.h>
#include <ctype.h>

int eof_flag = 0, err_flag;
int isvowel[256], tok;

int match(char *s, char *p)
{
	for (; *s && *p; s++, p++) {
		if (*p == 'C') {
			if (isvowel[*s]) return 0;
		} else {
			if (!isvowel[*s]) return 0;
		}
	}
	
	return (*s == '\0' && *p == '\0');
}

int next()
{
	static char s[65536];
	int n, c;

	if (eof_flag)
		return (tok = '.');

	while ((c = getchar()) != EOF && !isalpha(c) && c != '.' && c != '#');

	if (c == EOF || c == '#') {
		eof_flag = 1;
		return (tok = '.');
	}

	if (c == '.') {
		ungetc(c, stdin);
		return (tok = '.');
	}

	for (n = 0; c != EOF && isalpha(c); c = getchar())
		s[n++] = tolower(c);
	s[n] = '\0';

	if (c != EOF) ungetc(c, stdin);

	if (!isvowel[s[n - 1]])
		return (tok = 'N');

	if (n == 1)
		return (tok = 'A');

	if (n == 2 && (s[0] == 'g' || s[0] == 'b' || s[0] == 'd' || s[0] == 'l'))
		return (tok = toupper(s[0]));

	if (match(s, "CCVCV") || match(s, "CVCCV"))
		return (tok = 'P');

/*	err_flag = 1;*/
	return (tok = 'N');
}

void skip()
{
	int c;

	if (eof_flag == 0) {
		while ((c = getchar()) != EOF && c != '.' && c != '#');
		if (c == '#') ungetc(c, stdin);

		if (c == '.') {
			while ((c = getchar()) != EOF && c != '\n');
		}
	}
}

int check()
{
	int i;

	if (tok == 'D') {
		for (i = 0; next() == 'P'; i++);
		if (i < 1) return 0;

		while (tok == 'A') {
			for (i = 0; next() == 'P'; i++);
			if (i < 1) return 0;
		}

		return (tok == '.');
	}

	if (tok == 'N') {
		next();
	} else if (tok == 'L') {
		for (i = 0; next() == 'P'; i++);
		if (i < 1) return 0;
	} else {
		return 0;
	}

	if (tok == 'B') {
		for (i = 0; next() == 'P'; i++);
		if (i < 1) return 0;

		while (tok == 'A') {
			for (i = 0; next() == 'P'; i++);
			if (i < 1) return 0;
		}

		return (tok == '.');
	}

	if (tok != 'G')
		return 0;

	for (i = 0; next() == 'P'; i++);
	if (i < 1) return 0;

	if (tok == 'N') {
		next();
	} else if (tok == 'L') {
		for (i = 0; next() == 'P'; i++);
		if (i < 1) return 0;
	} else {
		return (tok == '.');
	}

	return (tok == '.');
	

/*
predstring -> P+
preds -> P+ (A P+)*
predname -> L P+
predname -> N
verbpred -> G P+

sentence -> predname G P+ predname
sentence -> predname G P+
sentence -> predname B P+ (A P+)*
sentence -> D P+ (A P+)*
*/

}

int main()
{
	char *s = "aeiouAEIOU";
	int r;

	memset(isvowel, 0, sizeof(isvowel));
	for (r = 0; s[r]; r++)
		isvowel[s[r]] = 1;

	for (;;) {
		err_flag = 0;

		next();

		r = check();
		if (eof_flag) break;

		skip();

		printf((!err_flag && r) ? "Good\n" : "Bad!\n");
	}	

	return 0;
}
