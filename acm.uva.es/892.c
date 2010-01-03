#include <stdio.h>
#include <ctype.h>

int main()
{
	char w[1024];
	int c, n, ln, hy;

	for (n = ln = hy = 0; (c = getchar()) != EOF;) {
		if (c == ' ' || c == '\n') {
			if (n > 0) {
				if (hy) putchar('\n');
				fwrite(w, 1, n, stdout);
				if (hy) putchar('\n');
				hy = n = 0;
			}

			if (c == '\n')
				ln = 0;

			putchar(c);

			continue;
		}

		ln++;

		if (isalpha(c)) {
			w[n++] = c;
			continue;
		}

		if (c == '#' && ln == 1) {
			c = getchar();
			if (c == '\n') break;
			ungetc(c, stdin);
			continue;
		}

		if (c == '-') {
			c = getchar();
			if (c != '\n') {
				ungetc(c, stdin);
				continue;
			}
			hy = 1;
			continue;
		}
	}

	if (n > 0) {
		fwrite(w, 1, n, stdout);
		n = 0;
	}

	return 0;
}
