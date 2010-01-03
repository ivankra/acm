#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
	char s[1024];
	int c, n;

	for (n = 0, c = getchar();;) {
		if (c == EOF) {
			break;
		} else if (c == '\0' || c == ' ' || c == '\t' || c == '\r') {
			c = getchar();
		} else if (c == '\n') {
			if ((c = getchar()) != '~') continue;
			if ((c = getchar()) != '~') continue;

			gets(s);
			printf("Program by %s contains %d units.\n", s, n);

			n = 0;
			c = getchar();
		} else if (strchr("([+-*/=@^", c) != NULL) {
			n++;
			c = getchar();
		} else if (c == '<') {
			n++;
			c = getchar();
			if (c == '>' || c == '=') c = getchar();
		} else if (c == '>') {
			n++;
			c = getchar();
			if (c == '=') c = getchar();
		} else if (c == ':') {
			c = getchar();
			if (c == '=') { n++; c = getchar(); }
		} else if (c == '{') {
			c = getchar();
			while (c != EOF && c != '}')
				c = getchar();
			if (c == '}') c = getchar();
		} else if (c == '\'') {
			for (c = getchar(); c != EOF;) {
				if (c == '\'') {
					c = getchar();
					if (c != '\'') break;
				}
				c = getchar();
			}
			n++;
		} else if (isalpha(c) || c == '_') {
			for (n++; c != EOF && (isalnum(c) || c == '_');)
				c = getchar();
		} else if (c == '$') {
			for (n++, c = getchar(); c != EOF && isxdigit(c);)
				c = getchar();
		} else if (isdigit(c)) {
			n++;

			while (isdigit(c))
				c = getchar();

			if (c == '.') {
				while (isdigit(c = getchar()));
			}

			if (c == 'e' || c == 'E') {
				c = getchar();
				if (c == '+' || c == '-') c = getchar();

				while (isdigit(c))
					c = getchar();
			}
		} else {
			c = getchar();
		}
	}

	return 0;
}
