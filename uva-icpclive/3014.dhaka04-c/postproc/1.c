#include <stdio.h>

int main()
{
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\\') {
			c=getchar();
			if (c == '\n') continue;
		}
		putchar(c);
	}
}
