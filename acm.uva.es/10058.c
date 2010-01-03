#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *tokp;
int tok, err;

int next()
{
	static char *n[] = { "tom", "jerry", "goofy", "mickey", "jimmy", "dog", "cat", "mouse", NULL };
	static char *v[] = { "hate", "love", "know", "like", "hates", "loved", "knows", "likes", NULL };
	static char s[1024];
	int i;

	if (err)
		return (tok = 0);

	while (*tokp && !isalpha(*tokp) && *tokp != ',')
		tokp++;

	if (*tokp == '\0')
		return (tok = 0);

	if (*tokp == ',')
		return (tok = *tokp++);

	for (i = 0; *tokp && isalpha(*tokp); tokp++)
		s[i++] = *tokp;
	s[i] = 0;

	if (strcmp(s, "and") == 0)
		return (tok = '&');

	if (strcmp(s, "a") == 0 || strcmp(s, "the") == 0)
		return (tok = 'a');

	for (i = 0; v[i]; i++)
		if (strcmp(s, v[i]) == 0) return (tok = 'v');

	for (i = 0; n[i]; i++)
		if (strcmp(s, n[i]) == 0) return (tok = 'n');

	err = 1;
	return (tok = 0);
}

int action()
{
	for (;;) {
		if (tok == 'a') next();
		if (tok != 'n') return 0;
		next();
		if (tok == '&')
			next();
		else
			break;
	}

	if (tok != 'v')
		return 0;
	next();

	for (;;) {
		if (tok == 'a') next();
		if (tok != 'n') return 0;
		next();
		if (tok == '&')
			next();
		else
			break;
	}

	return 1;
}

int solve()
{
	while (tok != 0) {
		if (!action())
			return 0;

		if (tok == ',')
			next();
		else if (tok == 0)
			return 1;
	}

	return 0;
}

int main()
{
	static char s[65536];
	while (gets(s)) {
		err = 0;
		tokp = s;
		next();
		printf((solve() && err == 0) ? "YES I WILL\n" : "NO I WON'T\n");
	}

	return 0;
}
