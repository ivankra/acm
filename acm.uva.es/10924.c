#include <stdio.h>

int map[256], e[2048];
char s[1024];

int main()
{
	int i, j;

	for (i = 'a', j = 1; i <= 'z'; i++, j++) map[i] = j;
	for (i = 'A', j = 27; i <= 'Z'; i++, j++) map[i] = j;

	for (i = 2; i < 50; i++)
		if (e[i] == 0) for (j = i * i; j < 2048; j += i) e[j] = 1;

	while (scanf(" %s", s) == 1) {
		for (j = 0, i = 0; s[i]; i++)
			j += map[(unsigned)s[i]];

		printf("It is %sa prime word.\n", e[j] ? "not " : "");
	}

	return 0;
}
