#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
	char buf[1024], *s;
	int k[32], i, n, t;

	printf(
		"+----------+----------------+-----------------------------+\n"
		"| Keyboard | # of printable | Additionally, the following |\n"
		"|          |      lines     |  letter keys can be broken  |\n"
		"+----------+----------------+-----------------------------+\n"
	);

	for (t = 1; gets(buf) && strcmp(buf, "finish") != 0; t++) {
		memset(k, 0, sizeof(k));

		for (s = buf; *s; s++)
			if (isalpha(*s)) k[toupper(*s) - 'A'] = -1;

		for (n = 0; gets(buf);) {
			for (s = buf; *s; s++)
				if (isalpha(*s) && k[toupper(*s) - 'A'] < 0) break;

			if (*s == '\0') {
				for (n++, s = buf; *s; s++)
					if (isalpha(*s)) k[toupper(*s) - 'A'] = 1;
			}

			if (strcmp(buf, "END") == 0)
				break;
		}


		printf("|%6d    |%9d       | ", t, n);

		for (i = 0, n = 0; i < 26; i++)
			if (k[i] == 0) n++, putchar(i + 'a');

		for (; n < 28; n++)
			putchar(' ');

		printf("|\n+----------+----------------+-----------------------------+\n");
	}

	return 0;
}
