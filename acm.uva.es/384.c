#include <stdio.h>

static int check(char *s)
{
	register int i, c;

	for (c = 0;;) {
		if (*s++ != 'A') return 0;
		if (*s == 'H') { s++; break; }

		if (*s == 'B') {
			s++;
			c++;
			continue;
		}

		for (c++, i = 0; *s == 'D'; i++) {
			if (*++s != 'F') return 0;
			while (*s == 'F') s++;
		}
		if (*s++ != 'G' || i == 0) return 0;

		break;
	}

	while (c-- > 0)
		if (*s++ != 'C') return 0;

	for (i = 0; *s == 'D'; i++) {
		if (*++s != 'F') return 0;
		while (*s == 'F') s++;
	}
	if (*s++ != 'G' || i == 0) return 0;

	return (*s == '\0');
}

int main()
{
	static char s[1024], map[256];
	static int t;
	register int i;

	for (i = 0; i < 256; i++)
		map[i] = ((i >= 'a' && i <= 'z') ? (i - 'a' + 'A') :
			  (i >= 'A' && i <= 'Z') ? i : 0);
	map['E'] = 'D';

	printf("SLURPYS OUTPUT\n");
	for (scanf("%d", &t); t-- > 0 && scanf(" %[A-Za-z]", s) == 1;) {
		for (i = 0; s[i]; i++) s[i] = map[(unsigned)s[i]];
		printf(check(s) ? "YES\n" : "NO\n");
	}
	printf("END OF OUTPUT\n");
	return 0;
}
