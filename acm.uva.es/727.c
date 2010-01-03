#include <stdio.h>
#include <string.h>

static int token;

static int next()
{
	while ((token = getchar()) != EOF)
		if (strchr("0123456789+-*/()", token) != NULL) break;
	return token;
}

static void expr(void);

static void factor()
{
	if (token >= '0' && token <= '9') {
		putchar(token);
		next();
	} else if (token >= '(') {
		next();
		expr();
		if (token == ')') next();
	}
}

static void term()
{
	int c;

	for (factor(); token == '*' || token == '/';) {
		c = token;
		next();
		factor();
		putchar(c);
	}
}

static void expr()
{
	int c;

	for (term(); token == '+' || token == '-';) {
		c = token;
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

	while (t-- > 0) {
		expr();
		putchar('\n');

		if (t > 0) putchar('\n');
	}

	return 0;
}

