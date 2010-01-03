#include <stdio.h>
#include <string.h>

char s[1024];
int got[128][128], tab[128][128];

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int check(int offs, int len)
{
	int i, k, m, r, in, out;

	if (got[offs][len])
		return tab[offs][len];

	got[offs][len] = 1;

	if (len == 0)
		return (tab[offs][len] = 1);

	if (len <= 1)
		return (tab[offs][len] = 0);

	for (r = 0, m = 2; m <= len; m++) {
		out = check(offs + m, len - m);
		if (out == 0) continue;

		for (in = 0, k = 1; (2 * k) <= m; k++) {
			for (i = 0; i < k; i++)
				if (s[offs + i] != s[offs + m - 1 - i]) break;
			if (i < k) continue;

			in = max(in, check(offs + k, m - 2 * k));
			if (in >= 2) return (tab[offs][len] = 2);
		}

		r += in * out;
		if (r >= 2) return (tab[offs][len] = 2);
	}

	return (tab[offs][len] = r);
}

char *answer()
{
	int k;

	memset(got, 0, sizeof(got));
	k = check(0, strlen(s));

	if (k == 0)
		return "Invalid";
	else if (k == 1)
		return "Valid, Unique";
	else
		return "Valid, Multiple";
}

int main()
{
	int c, t;

	for (scanf("%d", &t), c = 1; c <= t && scanf(" %[a-z]", s) == 1; c++)
		printf("Case %d: %s\n", c, answer());

	return 0;
}
