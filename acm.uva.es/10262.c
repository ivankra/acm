#include <stdio.h>
#include <string.h>

#define MAX 2048

int pal(char *s)
{
	char *p;
	for (p = s; *p; p++);
	while (*s) if (*s++ != *--p) return 0;
	return 1;
}

void filt(char *s)
{
	char *t;
	for (t = s; *s; s++)
		if ('a' <= (*s) && (*s) <= 'z') *t++ = *s;
	*t = '\0';
}

int check(char *a, char *b, char *r)
{
	static char t[2*MAX];

	sprintf(t, "%s%s", a, r);
	if (!pal(t)) return 0;

	sprintf(t, "%s%s", b, r);
	if (pal(t)) return 0;

	return 1;
}

int sol(char *a, char *b, char *r)
{
	static char t[2*MAX];
	int i, j, k, n;

	n = strlen(a);

	for (i = 0; i <= n; i++) {
		for (j = i - 1, k = 0; j >= 0; j--)
			r[k++] = a[j];
		r[k] = '\0';
		if (check(a, b, r)) return 0;
	}

	for (j = n - 1, k = 1; j >= 0; j--)
		r[k++] = a[j];
	r[k] = '\0';

	for (r[0] = 'a'; r[0] <= 'z'; r[0]++)
		if (check(a, b, r)) return 0;

	return 1;
}

char *solve(char *a, char *b)
{
	static char r[MAX], s[MAX];

	if (strcmp(a, b) == 0) return NULL;

	if (sol(a, b, r)) {
		if (sol(b, a, s)) return NULL;
		return s;
	}

	if (sol(b, a, s))
		return r;

	if (strlen(r) != strlen(s))
		return (strlen(r) < strlen(s)) ? r : s;

	return (strcmp(r, s) < 0) ? r : s;
}

int main()
{
	static char a[MAX], b[MAX];
	char *r;

	while (gets(a) && gets(b)) {
		filt(a); filt(b);
		r = solve(a, b);
		printf(r ? "%s\n" : "No solution.\n", r);
	}

	return 0;
}
