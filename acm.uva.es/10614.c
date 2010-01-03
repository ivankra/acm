#include <stdio.h>
#include <ctype.h>

typedef struct {
	int dim, v[3];
} value_t;

static int la, la_num;
static char *tokptr;

static int next()
{
	register char *p;

	while (*tokptr == ' ')
		tokptr++;

	if (*tokptr == '\0')
		return (la = 0);

	for (p = "+-*x,[]()"; *p; p++)
		if (*tokptr == *p) return (la = *tokptr++);

	if (*tokptr >= '0' && *tokptr <= '9') {
		for (la_num = 0; *tokptr >= '0' && *tokptr <= '9';)
			la_num = la_num * 10 + *tokptr++ - '0';
		return (la = 'n');
	}

	return (la = -1);
}

static int expr(value_t *);

static int primary(value_t *r)
{
	if (la == 'n') {
		r->dim = 1;
		r->v[0] = la_num;
		next();
		return 0;
	}

	if (la == '(') {
		if (next() <= 0 || expr(r) || la != ')') return 1;
		next();
		return 0;
	}

	if (la == '[') {
		value_t t;

		r->dim = 3;

		if (next() <= 0 || expr(&t) || t.dim != 1 || la != ',')
			return 1;
		r->v[0] = t.v[0];

		if (next() <= 0 || expr(&t) || t.dim != 1 || la != ',')
			return 1;
		r->v[1] = t.v[0];

		if (next() <= 0 || expr(&t) || t.dim != 1 || la != ']')
			return 1;
		r->v[2] = t.v[0];

		next();

		return 0;
	}

	return 1;
}

static int term(value_t *r)
{
	value_t t, u;
	int op, i, v;

	if (primary(r)) return 1;

	while (la == '*' || la == 'x') {
		op = la;

		if (next() <= 0 || primary(&t))
			return 1;

		if (op == '*') {
			if (r->dim == t.dim) {
				for (i = 0, v = 0; i < t.dim; i++)
					v += r->v[i] * t.v[i];
				r->v[0] = v;
				r->dim = 1;
			} else if (r->dim == 3) {
				for (i = 0; i < 3; i++)
					r->v[i] *= t.v[0];
			} else {
				for (v = r->v[0], i = 0; i < 3; i++)
					r->v[i] = t.v[i] * v;
				r->dim = 3;
			}
		} else {
			if (r->dim != 3 || t.dim != 3)
				return 1;

			for (i = 0; i < 3; i++)
				u.v[i] = r->v[i];

			r->v[0] = u.v[1] * t.v[2] - u.v[2] * t.v[1];
			r->v[1] = u.v[2] * t.v[0] - u.v[0] * t.v[2];
			r->v[2] = u.v[0] * t.v[1] - u.v[1] * t.v[0];
		}
	}

	return 0;
}

static int expr(value_t *r)
{
	value_t t;
	int op, i;

	if (term(r))
		return 1;

	while (la == '+' || la == '-') {
		op = la;

		if (next() <= 0 || term(&t) || r->dim != t.dim)
			return 1;

		for (i = 0; i < t.dim; i++)
			r->v[i] += (op == '+') ? t.v[i] : (-t.v[i]);
	}

	return 0;
}

int main()
{
	static char buf[1024];
	static value_t r;
	int i;

	while (fgets(buf, sizeof(buf), stdin)) {
		for (i = 0; buf[i] && buf[i] != '#' && buf[i] != '\n'; i++);

		if (buf[i] == '#') break;
		buf[i] = '\0';

		tokptr = buf;
		next();

		if (expr(&r) || la != 0)
			printf("Bang!\n");
		else if (r.dim == 1)
			printf("%d\n", r.v[0]);
		else
			printf("[%d,%d,%d]\n", r.v[0], r.v[1], r.v[2]);
	}

	return 0;
}
