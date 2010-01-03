#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef unsigned long long num;

num c[64];
char *p;

num eval(int v)
{
	num r;
	int i;

	assert(v < 2 || *p == '(' || ('0' <= *p && *p <= '9'));

	if (v < 2) {
		r = eval(v + 1);
		for (i = 0; *p == "+*"[v]; i++) {
			p++;
			r *= eval(v + 1);
		}
		return r * c[i];
	} else if (*p++ == '(') {
		r = eval(0);
		assert(*p == ')');
		p++;
		return r;
	} else {
		return 1;
	}
}

int main()
{
	static char s[2048];
	int i, j;

	for (c[0] = 1, i = 1; i < 40; i++)
		for (c[i] = 0, j = 0; j < i; j++)
			c[i] += c[j] * c[i - 1 - j];

	while (gets(s)) {
		for (p = s, i = 0, j = 0; s[j]; j++)
			if (strchr("0123456789+*()", s[j]) != NULL) s[i++] = s[j];
		s[i] = '\0';

		printf("%llu\n", eval(0));

		assert(*p == '\0');
	}

	return 0;
}
