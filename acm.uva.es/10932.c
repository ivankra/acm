#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char buf[1048576], *tok;
double var[32];

double eval(void);

double fact()
{
	if (isalpha(tok[0])) {
		tok++;
		return var[toupper(tok[-1]) - 'A'];
	}

	if (isdigit(tok[0]) || tok[0] == '.') {
		int n; double r;
		sscanf(tok, "%lf%n", &r, &n); tok += n;
		return r;
	}

	if (tok[0] == '(') {
		double r;
		tok++;
		r = eval();
		if (*tok++ != ')') abort();
		return r;
	}

	abort();
}

double term()
{
	double r;
	for (r = fact();;)
		if (tok[0] == '*')
			tok++, r *= fact();
		else if (tok[0] == '/')
			tok++, r /= fact();
		else
			return r;
}

double eval()
{
	double r;
	for (r = term();;)
		if (tok[0] == '+')
			tok++, r += term();
		else if (tok[0] == '-')
			tok++, r -= term();
		else
			return r;
}

int main()
{
	int i;

	for (i = 0; i < 32; i++) var[i] = 0.;
	while (gets(buf)) {
		tok = buf;
		if (isalpha(*tok) && tok[1] == '=') {
			tok += 2;
			var[toupper(buf[0]) - 'A'] = eval();
		} else {
			printf("%.2f\n", eval());
		}
	}

	return 0;
}
