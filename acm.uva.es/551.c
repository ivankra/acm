#include <stdio.h>

static int check(const char *s)
{
	static int p[4096];
	int i, m, n;

	for (n = 0, m = 1;; m++) {
		if (*s == '{' || *s == '[' || *s == '<') {
			p[n++] = *s++;
		} else if (*s == '(') {
			if (s[1] == '*') {
				p[n++] = '*';
				s += 2;
			} else {
				p[n++] = '(';
				s++;
			}
		} else if (*s == '}') {
			if (n == 0 || p[--n] != '{') return m;
			s++;
		} else if (*s == '>') {
			if (n == 0 || p[--n] != '<') return m;
			s++;
		} else if (*s == ']') {
			if (n == 0 || p[--n] != '[') return m;
			s++;
		} else if (*s == ')') {
			if (n == 0 || p[--n] != '(') return m;
			s++;
		} else if (*s == '*' && s[1] == ')') {
			if (n == 0 || p[--n] != '*') return m;
			s += 2;
		} else if (*s == '\0' || *s == '\n' || *s == '\r') {
			return (n == 0) ? 0 : m;
		} else {
			s++;
		}
	}
}

int main()
{
	static char buf[4096];
	static int i;

	while (fgets(buf, sizeof(buf), stdin)) {
		i = check(buf);
		if (i == 0)
			printf("YES\n");
		else
			printf("NO %d\n", i);
	}

	return 0;
}
