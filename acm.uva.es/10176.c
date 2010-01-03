#include <stdio.h>

int main()
{
	int c, r;

	for (r = 0; (c = getchar()) != EOF;) {
		if (c == '0') {
			r = (r << 1) % 131071;
		} else if (c == '1') {
			r = ((r << 1) | 1) % 131071;
		} else if (c == '#') {
			printf(r ? "NO\n" : "YES\n");
			r = 0;
		}
	}

	return 0;
}
