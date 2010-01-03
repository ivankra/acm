#include <stdio.h>

int main()
{
	static char buf[4096], buf2[16];
	static int tab[256], b, w;
	unsigned long x;
	int i;
	char *p;

	for (i = 0; i < 256; i++)
		tab[i] = ((i >= '0' && i <= '9') ? (i - '0') :
			  ((i >= 'A' && i <= 'Z') ? (i - 'A' + 10) :
			   (i >= 'a' && i <= 'z') ? (i - 'a' + 10) : 0));

	while (scanf(" %[0-9A-Fa-f] %d %d", buf, &b, &w) > 0) {

		for (p = buf, x = 0; (x & 0xF0000000) == 0 && *p;)
			x = x * b + tab[*p++];

		if (x & 0xF0000000) {
			printf("  ERROR\n");
			continue;
		}

		for (i = 0; x > 0 || i == 0; x /= w)
			buf[i++] = "0123456789ABCDEF"[x % w];

		if (i > 7) {
			printf("  ERROR\n");
			continue;
		}

		while (i < 7)
			buf[i++] = ' ';

		for (p = buf2; i > 0;)
			*p++ = buf[--i];
		*p++ = '\0';

		printf("%s\n", buf2);
	}

	return 0;
}
