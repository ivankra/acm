#include <stdio.h>
#include <ctype.h>

char *p;

int alp(int c) { return (32 <= c && c < 128 && isalpha(c)); }
int sym(int c) { return (32 <= c && c < 128 && (isalnum(c) || (c == '_') || (c == '-'))); }

int word()
{
	if (!sym(*p)) return 0;
	while (sym(*p)) p++;
	return 1;
}

int check()
{
	int i;

	for (i = 0; word();) {
		if (*p == '.') {
			p++, i = 0;
		} else if (*p == '@') {
			i = 1; break;
		} else {
			return 0;
		}
	}
	if (i == 0 || *p != '@') return 0;
	p++;

	while (word()) {
		if (*p != '.') return 0;
		p++;
		if (alp(p[0]) && alp(p[1]) && p[2] == '\0') return 1;
		if (alp(p[0]) && alp(p[1]) && alp(p[2]) && p[3] == '\0') return 1;
	}

	return 0;
}

int main()
{
	char s[1024];
	int i, e, n;

	while (gets(s) && sscanf(s, "%d", &n) != 1);

	while (n-- > 0 && gets(s)) {
		e = 0;
		for (p = s; p[0] != '\0' && p[0] != '\n' && p[0] != '\r'; p++) {
			i = *(unsigned char *)p;
			if (i < 32 || i > 127) { e = 1; break; }
		}

		if (e) { printf("NO\n"); continue; }

#if 1
		p[0] = '\0';
		p = s;
#else
		while (p > s && p[-1] == ' ') p--;
		p[0] = '\0';
		p = s;
		while (*p == ' ') p++;
#endif

		printf(check() ? "YES\n" : "NO\n");
	}

	return 0;
}
