#include <stdio.h>
#include <ctype.h>

int s[65536], n;
char t[65536];

int main()
{
	int i, c;

/*	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
*/
	n = 0;
	while ((c = getchar()) != EOF) {
		if (c == '<') {
			t[0] = c;
			for (i = 1; (c = getchar()) != EOF && c != '>';)
				t[i++] = c;
			t[i++] = '>'; t[i] = 0;

			for (i = 0; t[i] != 0 && !isalpha(t[i]) && t[i] != '/'; i++);
			if (t[i] == 0) continue;

			c = tolower(t[i]);

			if (c == 'd' || c == 'D')
				s[n++] = 'd';
			else if (c == 'u' || c == 'U')
				s[n++] = 'u';
			else if (c == '/') {
				if (n > 0) n--;
			}
		} else {
			if (n < 1)
				putchar(c);
			else if (s[n-1] == 'u')
				putchar(toupper(c));
			else
				putchar(tolower(c));
		}
	}

	return 0;
}
