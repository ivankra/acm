#include <stdio.h>
#include <string.h>

#define MAX 1048576

int l[MAX], m;
char *p;

void pre(char *s)
{
	int i, j;

	for (p = s, l[0] = l[1] = 0, i = 1; s[i]; i++) {
		for (j = l[i]; j > 0 && s[i] != s[j]; j = l[j]);
		l[i+1] = (s[i] == s[j]) ? (j + 1) : 0;
	}
	m = i;
}

int match(char *s)
{
	int i, j;

	for (i = j = 0; s[i]; i++) {
		while (j > 0 && s[i] != p[j]) j = l[j];
		if (s[i] == p[j] && ++j >= m) return (i - m + 2);
	}

	return m;
}

int main()
{
	static char s[2*MAX];

	while (scanf(" %s", s) == 1 && s[0] != '.') {
		pre(s);
		memcpy(s + m, s, m); s[2 * m - 1] = '\0';
		printf("%d\n", m / match(s + 1));
	}

	return 0;
}
