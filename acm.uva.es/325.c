#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int check(char *p)
{
	if (*p == '-' || *p == '+')
		p++;

	if (*p == '\0' || !isdigit(*p))
		return 0;

	while (*p && isdigit(*p))
		p++;

	if (*p != '.' && *p != 'e' && *p != 'E')
		return 0;

	if (*p == '.') {
		p++;

		if (*p == '\0' || !isdigit(*p))
			return 0;

		while (*p && isdigit(*p))
			p++;
	}

	if (*p == 'e' || *p == 'E') {
		p++;

		if (*p == '+' || *p == '-')
			p++;

		if (*p == '\0' || !isdigit(*p))
			return 0;

		while (*p && isdigit(*p))
			p++;
	}

	return (*p == '\0');
}

int main()
{
	static char s[65536];
	int i, j;

	while (gets(s) && s[0] != '*') {
		for (i = 0; s[i] == ' ' || s[i] == '\t'; i++);

		if (i != 0) {
			for (j = 0; s[i] != '\0';)
				s[j++] = s[i++];
			s[j] = '\0';
		}

		for (i = 0; s[i] != '\0'; i++);
		for (i--; i >= 0 && (s[i] == ' ' || s[i] == '\t'); i--);
		s[i + 1] = '\0';

		printf("%s is %s.\n", s, check(s) ? "legal" : "illegal");
	}

	return 0;
}
