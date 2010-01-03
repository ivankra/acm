#include <stdio.h>

int main()
{
	int b, c;

	while ((c = getchar()) != EOF) {
		if (c != '|') continue;

		for (b = 0; ((c = getchar()) != EOF) && c != '|';)
			if (c == ' ') b <<= 1; else if (c == 'o') b = (b << 1) | 1;

		putchar(b & 0xFF);
	}

	return 0;
}
