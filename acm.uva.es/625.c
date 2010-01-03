#include <stdio.h>
#include <string.h>
#include <ctype.h>

char symtab[8192][64];
int nsym;

int lookup(char *s)
{
	int i;

	for (i = 0; i < nsym; i++)
		if (strcmp(symtab[i], s) == 0) return i;

	return -1;
}

int add(char *s)
{
	strcpy(symtab[nsym], s);
	return nsym++;
}

void clear()
{
	char *s[] = {
		"var", "end", "for", "then", "else", "case", "goto", "const",
		"label", "while", "begin", "until", "repeat", "downto",
		"function", "procedure", NULL
	};
	int i;

	for (nsym = 0, i = 0; s[i]; i++)
		add(s[i]);
}

void word(char *s, int k)
{
	int n;

	s[k] = '\0';

	if (k < 3) {
		printf("%s", s);
	} else if ((n = lookup(s)) >= 0) {
		printf("&%d", n);
	} else {
		add(s);
		printf("%s", s);
	}
}

void parse(char *s)
{
	static char w[65536];
	int k;

	for (k = 0; *s; s++) {
		if (isalnum(*s)) {
			w[k++] = *s;
		} else {
			if (k != 0) {
				word(w, k);
				k = 0;
			}
			putchar(*s);
		}
	}

	if (k != 0)
		word(w, k);
}

int main()
{
	static char s[65536];
	int t;

	while (gets(s) && sscanf(s, "%d", &t) != 1);
	gets(s);

	while (t-- > 0) {
		for (clear(); fgets(s, sizeof(s), stdin);) {
			parse(s);
			if (strcmp(s, "end.\n") == 0) break;
		}
	}

	return 0;
}
