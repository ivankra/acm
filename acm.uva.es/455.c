#include <stdio.h>

int main()
{
	static char buf[1024];
	int i, j, r, len, t;

	for (scanf("%d", &t); t-- > 0 && scanf(" %s", buf) == 1;) {
		for (len = 0; buf[len]; len++);

		for (r = 1; r < len; r++) {
			if ((len % r) != 0)
				continue;

			for (i = r, j = 0; i < len; i++) {
				if (buf[i] != buf[j]) break;
				if (++j == r) j = 0;
			}

			if (i >= len)
				break;
		}

		printf("%d\n", r);
		if (t > 0) printf("\n");
	}

	return 0;
}
