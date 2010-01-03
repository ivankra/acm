#include <stdio.h>

int main()
{
	static char s[65536];
	char *p;
	int r;

	while (scanf(" %[0-9]", s) == 1) {
		for (p = s; *p == '0'; p++);
		if (*p == 0) break;

		for (r = 0; *p; p++)
			r = (r * 10 + (*p) - '0') % 11;

		printf("%s is %s of 11.\n", s, r ? "not a multiple" : "a multiple");
	}

	return 0;
}
