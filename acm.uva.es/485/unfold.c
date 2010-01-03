#include <stdio.h>

int main()
{
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\\') {
			if ((c = getchar()) != '\n') {
				putchar('\\');
				putchar(c);
			}
		} else {
			putchar(c);
		}
	}

	return 0;
}

