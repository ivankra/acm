#include <stdio.h>

int main()
{
	int c, s;

	for (s = 0; (c = getchar()) != EOF;) {
		if (c == '\"') {
			if ((s++ & 1) == 0)
				printf("``");
			else
				printf("''");
		} else {
			putchar(c);
		}
	}

	return 0;
}
