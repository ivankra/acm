#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

int tok;
double tokval;

int next() {
	for (;;) {
		int c = getchar();
		if (c == EOF || strchr("+-*/^()\n", c) != NULL) return tok = c;
		if (isspace(c)) continue;
		if (isdigit(c) || c == '.') {
			ungetc(c, stdin);
			scanf(" %lf", &tokval);
			return tok = 'n';
		}
		fprintf(stderr, "Bad character: %c\n", c); abort();
	}
}

void skip(int t) { assert(tok == t); next(); }

double expr();

// numpar ::= number | '(' expr ')'
double numpar() {
	if (tok == 'n') { double x = tokval; skip('n'); return x; }
	skip('('); double x = expr(); skip(')'); return x;
}

// factor ::= numpar | numpar '^' factor
double factor() {
	double x = numpar();
	if (tok == '^') { skip('^'); x = pow(x, factor()); }
	return x;
}

// term ::= factor | term '*' factor | term '/' factor
double term() {
	double x = factor();
	for (;;) {
		if (tok == '*') { skip('*'); x *= factor(); }
		else if (tok == '/') { skip('/'); x /= factor(); }
		else return x;
	}
}

// expr ::= term | expr '+' term | expr '-' term
double expr() {
	double x = term();
	for (;;) {
		if (tok == '+') { skip('+'); x += term(); }
		else if (tok == '-') { skip('-'); x -= term(); }
		else return x;
	}
}

int main() {
	next();
	while (tok != EOF) {
		if (tok == '\n') { skip('\n'); continue; }
		printf("%.9g\n", expr());
	}
	return 0;
}
