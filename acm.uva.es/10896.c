#include <stdio.h>
#include <ctype.h>
#include <string.h>

char enc[1024], word[1024], s[1024];

int check(int key)
{
	char *p;
	int i, c;

	for (p = enc, i = 0; *p; p++) {
		if (islower(*p))
			c = 'a' + ((*p - 'a' + 26 /*???*/ - key) % 26);
		else
			c = *p;

		if (isalpha(c)) {
			s[i++] = c;
		} else if (i > 0) {
			s[i] = '\0';
			if (strcmp(s, word) == 0) return 1;
			i = 0;
		}
	}

	if (i > 0) {
		s[i] = '\0';
		if (strcmp(s, word) == 0) return 1;
	}

	return 0;
}

int main()
{
	int k, n;

	while (gets(s) && sscanf(s, "%d", &n) != 1);

	while (n-- > 0) {
		gets(enc);
		gets(word);

		for (k = 0; k < 26; k++)
			if (check(k)) printf("%c", k + 'a');
		printf("\n");
	}

	return 0;
}
