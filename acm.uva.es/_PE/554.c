#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define WIDTH 60

char dict[128][32];
int ndict;

void wr(char *s)
{
	int i, m;

	for (m = 0; *s;) {
		if (m >= WIDTH) {
			putchar('\n');
			m = 0;
		}

		if (isalpha(*s)) {
			for (i = 0; s[i] && isalpha(s[i]); i++);

			if ((m + i) > WIDTH) {
				putchar('\n');
				m = 0;
			}

			while (*s && isalpha(*s)) {
				putchar(*s++);
				m++;
			}
		} else {
			putchar(*s++);
			m++;
		}
	}

	putchar('\n');
}

int match(char *s, int k)
{
	static char w[1024];
	int i, c, r;

	for (r = 0, i = 0;; s++) {
		if (*s == 0) {
			c = 0;
		} else {
			c = isalpha(*s) ? (toupper(*s) - 'A' + 1) : 0;
			c = (c + 27 - k) % 27;
			c = c ? ('A' + c - 1) : ' ';
		}

		if (isalpha(c)) {
			w[i++] = c;
			continue;
		}

		if (i != 0) {
			w[i] = '\0';
			for (i = 0; i < ndict; i++) {
				if (strcmp(dict[i], w) == 0) {
					r++;
					break;
				}
			}
			i = 0;
		}

		if (*s == '\0')
			break;
	}

	return r;
}

int main()
{
	char s[256];
	int i, j, k, m;

	for (ndict = 0; gets(dict[ndict]) && dict[ndict][0] != '#'; ndict++);

	gets(s);

	for (k = m = 0, i = 0; i < 26; i++) {
		j = match(s, i);
		if (i == 0 || j > m) {
			k = i;
			m = j;
		}
	}

	for (i = 0; s[i]; i++) {
		j = isalpha(s[i]) ? (toupper(s[i]) - 'A' + 1) : 0;
		j = (j + 27 - k) % 27;
		s[i] = j ? (j + 'A' - 1) : ' ';
	}

	wr(s);

	return 0;
}
