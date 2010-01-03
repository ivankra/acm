#include <stdio.h>

int S(int x)
{
	int y;
	for (y = 0; x > 0; x /= 10)
		y += x % 10;
	return y;
}

int main()
{
	static char s[65536];
	int i, j;

	while (scanf(" %[0-9]", s) == 1) {
		for (i = 0, j = 0; s[j]; j++)
			i += s[j] - '0';

		if (i == 0)
			break;

		for (j = 1; i >= 10; i = S(i), j++);

		if ((i % 9) == 0)
			printf("%s is a multiple of 9 and has 9-degree %d.\n", s, j);
		else
			printf("%s is not a multiple of 9.\n", s);
	}

	return 0;
}
