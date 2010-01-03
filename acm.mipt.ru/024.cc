#include <cstdio>
#include <cstring>
#include <cctype>

int tok, tokn;

int next() {
	for (;;) {
		int c = getchar();
		if (c == EOF) return tok = EOF;
		if (isspace(c)) continue;
		if (strchr("-+*()", c) != NULL) return tok = c;
		if (isdigit(c)) {
			ungetc(c, stdin); scanf("%d", &tokn); return tok='n';
		}
	}
}

int expr();

int expr1() {
	while (tok == '+') next();
	if (tok == 'n') { int x = tokn; next(); return x; }
	if (tok == '-') { next(); return -expr1(); }
	if (tok == '(') { next(); int x = expr(); if (tok == ')') next(); return x; }
	return 0;
}

int expr() {
	for (int res = expr1();;) {
		if (tok == '+') next(), res += expr1();
		else if (tok == '-') next(), res -= expr1();
		else if (tok == '*') next(), res *= expr1();
		else return res;
	}
}

int main() {
	next();
	printf("%d\n", expr());	
}
