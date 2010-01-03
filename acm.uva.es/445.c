#include <stdio.h>

int main()
{
	int c, a, l;

	for (a = -1, l = 0;;) {
		c = getchar();

		if (c >= '0' && c <= '9') {
			a = ((a < 0) ? 0 : a) + c - '0';
		} else if (c == '!' || c == '\n') {
			a = -1;
			putchar('\n');
			l = 1;
		} else if ((c >= 'A' && c <= 'Z') || c == '*' || c == 'b') {
			if (a < 0) a = 1;
			if (c == 'b') c = ' ';
			while (a-- > 0)
				putchar(c);
			a = -1;
			l = 0;
		} else if (c == EOF) {
			if (l == 0)
				putchar('\n');
			break;
		}
	}

	return 0;
}
