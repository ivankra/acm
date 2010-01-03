#include <stdio.h>
#include <string.h>

int parse(char *s, int n)
{
	if (n == 1)
		return ((s[0] == 'A') ? 1 : 0);

	if (n >= 2 && s[n - 2] == 'A' && s[n - 1] == 'B')
		return (parse(s, n - 2) ? 2 : 0);

	if (n >= 2 && s[0] == 'B' && s[n - 1] == 'A')
		return (parse(s + 1, n - 2) ? 3 : 0);

	return 0;
}

int main()
{
	static char s[65536], t[65536];
	int i, k, n;

	while (gets(s) && sscanf(s, "%d", &n) != 1);

	while (n-- > 0 && gets(s)) {
		for (i = 0, k = 0; s[i]; i++)
			if (s[i] == 'A' || s[i] == 'B') t[k++] = s[i];
		t[k] = '\0';

		switch(parse(t, k)) {
			case 0: printf("MUTANT\n"); break;
			case 1: printf("SIMPLE\n"); break;
			case 2: printf("FULLY-GROWN\n"); break;
			case 3: printf("MUTAGENIC\n"); break;
		}
	}

	return 0;
}
