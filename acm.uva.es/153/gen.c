#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	static char s[256];
	int i, j, n, t;

	if (argc < 2)
		return 1;

	strcpy(s, argv[1]);
	n = strlen(s);

	for (;;) {
		printf("%s\n", s);

		for (j = n - 2; j >= 0; j--)
			if (s[j] < s[j + 1]) break;

		if (j < 0)
			break;

		for (i = n - 1; s[i] <= s[j]; i--);

		t = s[i];
		s[i] = s[j];
		s[j] = t;

		for (j++, i = n - 1; j < i;) {
			t = s[i];
			s[i--] = s[j];
			s[j++] = t;
		}
	}

	return 0;
}
