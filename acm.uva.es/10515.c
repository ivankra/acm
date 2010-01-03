#include <stdio.h>
#include <string.h>

int main()
{
	static char s[1024], t[1024];
	static unsigned char x[48];
	int i, c, r;
	char *p;

	while (scanf(" %[0-9] %[0-9]", s, t) == 2) {
		if (strcmp(s, "0") == 0 && strcmp(t, "0") == 0)
			break;

		memset(x, 0, sizeof(x));
		for (p = t; *p; p++) {
			for (c = *p - '0', i = 0; i < 48; i++) {
				c += (int)x[i] * 10;
				x[i] = (unsigned char)(c & 0xFF);
				c >>= 8;
			}
		}

		c = s[strlen(s) - 1] - '0';
		r = 1;

		for (i = 0; i < (48 * 8); i++) {
			if (((x[i >> 3] >> (i & 7)) & 1) != 0)
				r = (r * c) % 10;
			c = (c * c) % 10;
		}

		printf("%d\n", r);
	}

	return 0;
}
