#include <stdio.h>
#include <string.h>
#include <assert.h>

#define INF 0x7FFFFFFF

int plus[1024], n;
char *name[1024], *ext[1024], txtbuf[1048576], *txt;

int min(int x, int y) { return (x < y) ? x : y; }

void make(char *pat, char *s[])
{
	int i, j, m;

	m = INF;
	for (i = 0; i < n; i++)
		if (plus[i] == '-') m = min(m, strlen(s[i]));
	assert(m < INF);

	for (i = 0; plus[i] != '-'; i++);
	strcpy(pat, s[i]); pat[m] = '\0';

	for (i = 0; i < n; i++) {
		if (plus[i] != '-') continue;
		for (j = 0; j < m; j++)
			if (pat[j] != s[i][j]) pat[j] = '?';
	}

	for (i = 0; i < n; i++)
		if (plus[i] == '-' && strlen(s[i]) > m) {
			strcat(pat, "*");
			break;
		}
}

int match(char *s, char *p)
{
	for (; *s && *p && *p != '*'; s++, p++)
		if (*p != '?' && *s != *p) return 0;

	if (*p == '*') return 1;
	if (*p == '\0' && *s == '\0') return 1;

	return 0;
}

int main()
{
	char buf[1024], pat1[1024], pat2[1024], *p;
	int i, t;

	while (gets(buf) && sscanf(buf, "%d", &t) != 1);
	gets(buf);

	while (t-- > 0) {
		txt = txtbuf;
		for (n = 0; gets(buf); n++) {
			for (i = 0; buf[i] && buf[i] != '\n' && buf[i] != '\r'; i++);
			if (i == 0) break;
			buf[i] = '\0';

			assert(n <= 1020);
			assert(buf[0] == '+' || buf[0] == '-');

			plus[n] = buf[0];
			for (p = buf + 1, name[n] = txt; *p && *p != '.';)
				*txt++ = *p++;
			*txt++ = '\0';
			if (*p == '.') p++;
			for (ext[n] = txt; *p;)
				*txt++ = *p++;
			*txt++ = '\0';
		}

		make(pat1, name);
		make(pat2, ext);

		for (i = 0; i < n; i++)
			if (plus[i] == '+' &&
			    match(name[i], pat1) && match(ext[i], pat2))
				break;

		if (i < n)
			printf("IMPOSSIBLE\n");
		else
			printf("DEL %s.%s\n", pat1, pat2);

		if (t) printf("\n");
	}

	return 0;
}
