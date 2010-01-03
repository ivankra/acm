#include <stdio.h>
#include <memory.h>

int main()
{
	static char buf[65536];
	static int vtab[256];
	int i, n, c;

	memset(vtab, 0, sizeof(vtab));
	for (i = 0; c = "aAeEiIoOuU"[i]; i++)
		vtab[c] = 1;

	for (n = 0;;) {
		c = getchar();
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			buf[n++] = c;
			continue;
		}

		if (n != 0) {
			buf[n] = '\0';

			if (vtab[(int)buf[0]])
				printf("%say", buf);
			else
				printf("%s%cay", buf + 1, buf[0]);

			n = 0;
		}

		if (c == EOF)
			break;

		putchar(c);
	}

	return 0;
}
