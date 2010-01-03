#include <stdio.h>
#include <ctype.h>

static long long num[256];
static char op[256];

static void parse(char *s)
{
	static int n, k;

	while (*s && (*s < '0' || *s > '9'))
		s++;

	for (n = 0; *s >= '0' && *s <= '9';)
		n = n * 10 + *s++ - '0';
	num[0] = (long long)n;

	for (k = 0; *s;) {
		while (*s && (*s != '+' && *s != '*')) s++;

		if (*s == '\0')
			break;

		op[k] = *s++;

		while (*s && (*s < '0' || *s > '9'))
			s++;

		for (n = 0; *s >= '0' && *s <= '9';)
			n = n * 10 + *s++ - '0';

		num[++k] = (long long)n;
	}

	op[k] = 0;
}

static long long evalmax()
{
	long long r, t;
	int i;

	for (t = num[0], i = 0; op[i] == '+';)
		t += num[++i];

	for (r = t; op[i] == '*';) {
		for (t = num[++i]; op[i] == '+';)
			t += num[++i];
		r *= t;
	}

	return r;
}

static long long evalmin()
{
	long long r, t;
	int i;

	for (t = num[0], i = 0; op[i] == '*';)
		t *= num[++i];

	for (r = t; op[i] == '+';) {
		for (t = num[++i]; op[i] == '*';)
			t *= num[++i];
		r += t;
	}

	return r;
}

int main()
{
	static char buf[4096];
	static int t;

	scanf("%d\n", &t);

	while (t-- > 0 && gets(buf)) {
		parse(buf);

		printf("The maximum and minimum are %lld and %lld.\n",
			evalmax(), evalmin());
	}

	return 0;
}
