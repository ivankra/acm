#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 256

static int read(char *s)
{
	int i, j;

	if (fgets(s, MAXLEN, stdin) == NULL) return 0;

	for (i = 0, j = 0; s[i] && s[i] != '#' && s[i] != '\n' && s[i] != '\r'; i++)
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[j++] = s[i];
		else if (s[i] >= 'a' && s[i] <= 'z')
			s[j++] = s[i] - 'a' + 'A';

	s[j] = '\0';
	return (j == 0) ? 0 : 1;
}

int main()
{
	static char a[MAXLEN], b[MAXLEN], t[32][32], r[32], u[32];
	int i, j, k;

	memset(t, 0, sizeof(t));
	memset(u, 0, sizeof(u));

	read(a);
	for (i = 0; a[i]; i++)
		u[a[i] - 'A'] = 1;

	while (read(b)) {
		for (i = 0; a[i] && b[i]; i++)
			if (a[i] != b[i]) {
				t[a[i] - 'A'][b[i] - 'A'] = 1;
				break;
			}

		for (i = 0; b[i]; i++)
			u[b[i] - 'A'] = 1;

		strcpy(a, b);
	}

	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			if (t[j][i] == 0) continue;
			for (k = 0; k < 26; k++)
				if (t[k][j]) t[k][i] = 1;
		}
	}

	for (i = 0; i < 26; i++)
		for (r[i] = 0, j = 0; j < 26; j++)
			r[i] += t[j][i];
	/* r[i]: number of elements less than i-th */

	memset(a, 0, sizeof(a));
	for (i = 0; i < 26; i++)
		if (u[i])
			a[r[i]] = 'A' + i;

	for (i = 0; i < 26; i++)
		if (a[i])
			putchar(a[i]);
	putchar('\n');

	return 0;
}
