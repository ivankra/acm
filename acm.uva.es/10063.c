#include <stdio.h>

static char input[64], inlen;

static void insert(char *perm, int n)
{
	char s[16];
	int i;

	if (n == inlen) {
		printf("%s\n", perm);
		return;
	}

	for (i = 0; i < n; i++)
		s[i + 1] = perm[i];
	s[n + 1] = '\0';

	for (i = 0; i <= n; i++) {
		s[i] = input[n];
		insert(s, n + 1);
		s[i] = s[i + 1];
	}
}

int main()
{
	int t;

	for (t = 0; scanf(" %[a-zA-Z]", input) == 1; t++) {
		if (t != 0)
			printf("\n");

		inlen = strlen(input);
		insert("", 0);
	}

	return 0;
}
