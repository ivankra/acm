#include <stdio.h>

static char line[8192], *tokp;
static int token;
static long long tokval;

static int next()
{
	if (*tokp == '+' || *tokp == '*' || *tokp == '(' || *tokp == ')')
		return (token = *tokp++);

	if (*tokp >= '0' && *tokp <= '9') {
		for (tokval = 0; *tokp >= '0' && *tokp <= '9'; tokp++)
			tokval = tokval * 10 + *tokp - '0';
		return (token = 'n');
	}

	return (token = 0);
}

static int expr(long long *r);

static int factor(long long *r)
{
	if (token == 'n') {
		(*r) = tokval;
		next();
		return 0;
	} else if (token == '(') {
		next();
		expr(r);
		if (token != ')')
			return 1;
		next();
		return 0;
	} else {
		return 1;
	}
}

static int term(long long *r)
{
	long long t;

	if (factor(r))
		return 1;

	while (token == '*') {
		next();
		if (factor(&t))
			return 1;
		(*r) *= t;
	}

	return 0;
}

static int expr(long long *r)
{
	long long t;

	if (term(r))
		return 1;

	while (token == '+') {
		next();
		if (term(&t))
			return 1;
		(*r) += t;
	}

	return 0;
}

int main()
{
	int t;
	long long r;

	for (scanf("%d\n", &t); t-- > 0 && gets(line);) {
		tokp = line;
		next();

		if (expr(&r) == 0 && *tokp == '\0')
			printf("%lld\n", r);
		else
			printf("ERROR\n");
	}

	return 0;
}
