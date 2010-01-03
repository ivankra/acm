#include <stdio.h>

static char s[] =
        "01528392877847384154459627362112817285988930617065562516293223740"
        "51409906950637667184958433403940710";

int main()
{
	static char buf[65536];
	register char *p;
	register int a, b, k;

	while (gets(buf)) {
		for (p = buf, a = 0, b = 0, k = 0; *p; p++)
			if (*p >= '0' && *p <= '9') {
				if (*p != '0') k++;
				a = b;
				b = *p - '0';
			}

		if (k == 0)
			break;

		printf("%c\n", s[a * 10 + b]);
	}

	return 0;
}
