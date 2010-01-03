#include <stdio.h>
#include <string.h>

int main()
{
	static char s[65536];
	int k, t;

	for (scanf("%d", &t); t-- > 0 && scanf(" %[0-9]", s) == 1;) {
		k = strlen(s);

		if (strcmp(s, "1") == 0 || strcmp(s, "4") == 0 ||
		    strcmp(s, "78") == 0)
			printf("+");
		else if (k >= 2 && s[k - 2] == '3' && s[k - 1] == '5')
			printf("-");
		else if (k >= 2 && s[0] == '9' && s[k - 1] == '4')
			printf("*");
		else
			printf("?");

		if (t != 0) printf("\n");
	}

	return 0;
}
