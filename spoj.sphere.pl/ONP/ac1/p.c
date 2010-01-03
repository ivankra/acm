#include <stdio.h>

int tok;

int next()
{
	for (;;) {
		tok = getchar();
		if (tok == EOF) return (tok = 0);
		if (tok == ' ' || tok == '\t' || tok == '\r' || tok == '\n')
			continue;
		return tok;
	}
}

void expr(void);

void primary()
{
	if ((tok >= 'a' && tok <= 'z') || (tok >= 'A' && tok <= 'Z')) {
		putchar(tok);
		next();
	} else if (tok == '(') {
		next();
		expr();
		if (tok == ')') next();
	}
}

void expon()
{
	for (primary(); tok == '^';) {
		next();
		primary();
		putchar('^');
	}
}

void term()
{
	int c;

	for (expon(); tok == '*' || tok == '/';) {
		c = tok;
		next();
		expon();
		putchar(c);
	}
}

void expr()
{
	int c;

	for (term(); tok == '+' || tok == '-';) {
		c = tok;
		next();
		term();
		putchar(c);
	}
}

int main()
{
	int t;

	scanf("%d", &t);
	next();

	while (t-- > 0 && tok != 0) {
		expr();
		putchar('\n');
	}

	return 0;
}
