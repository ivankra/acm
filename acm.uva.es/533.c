#include <stdio.h>

typedef struct {
	int a, b;	/* ax + b */
} expr_t;

static int tok, tok_num;
static char *tokptr;

static int next()
{
	for (; *tokptr; tokptr++) {
		if (*tokptr >= '0' && *tokptr <= '9') {
			for (tok_num = 0; *tokptr >= '0' && *tokptr <= '9';)
				tok_num = tok_num * 10 + *tokptr++ - '0';
			return (tok = 'n');
		}

		switch (*tokptr) {
			case '+': case '-': case '*': case '(': case ')':
			case '=':
				return (tok = *tokptr++);
			case 'x': case 'X':
				tokptr++;
				return (tok = 'x');
		}
	}

	return 0;
}

static void expr(expr_t *);

static void factor(expr_t *r)
{
	if (tok == 'n') {
		r->a = 0;
		r->b = tok_num;
		next();
	} else if (tok == 'x') {
		r->a = 1;
		r->b = 0;
		next();
	} else if (tok == '(') {
		next();
		expr(r);
		if (tok == ')') next();
	}
}

static void term(expr_t *r)
{
	expr_t t;

	factor(r);
	while (tok == '*') {
		next();
		factor(&t);
		r->a = r->a * t.b + r->b * t.a;
		r->b *= t.b;
	}
}

static void expr(expr_t *r)
{
	expr_t t;
	int op;

	term(r);
	while (tok == '+' || tok == '-') {
		op = tok;

		next();
		term(&t);

		if (op == '+') {
			r->a += t.a;
			r->b += t.b;
		} else {
			r->a -= t.a;
			r->b -= t.b;
		}
	}
}

int main()
{
	static char buffer[4096];
	static expr_t eq, rhs;
	static int t;

	for (t = 1; gets(buffer); t++) {
		if (t > 1)
			printf("\n");

		tokptr = buffer;
		next();

		expr(&eq);
		if (tok == '=') next();
		expr(&rhs);

		eq.a -= rhs.a;
		eq.b -= rhs.b;

		/* eq.a x + eq.b x == 0 */

		printf("Equation #%d\n", t);

		if (eq.a == 0 && eq.b == 0)
			printf("Infinitely many solutions.\n");
		else if (eq.a == 0 && eq.b != 0)
			printf("No solution.\n");
		else
			printf("x = %.6f\n", -(double)eq.b / (double)eq.a);
	}

	return 0;
}
