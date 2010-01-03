#include <stdio.h>
#include <ctype.h>

int main()
{
	int s, c;

	for (s = 1; (c = getchar()) != EOF;) {
		if (c != '\\') {
			putchar(c);
			continue;
		}

		if (s == 0) {
			if ((c = getchar()) == '*') {
				s = 1;
				continue;
			}

			putchar('\\');
			if (c != EOF) ungetc(c, stdin);
			continue;
		}

		c = getchar();
		if (c == '*') {
			s = 0;
		} else if (c == 'b' || c == 'i') {
			continue;
		} else if (c == 's') {
			for (c = getchar(); c != EOF && isdigit(c);)
				c = getchar();

			if (c == '.')
				for (c = getchar(); c != EOF && isdigit(c);)
					c = getchar();

			if (c != EOF)
				ungetc(c, stdin);
		} else {
			putchar(c);
		}
	}

	return 0;
}
