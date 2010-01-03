#include <stdio.h>

int main()
{
	int c, w, n;

	for (w = 0, n = 0;;) {
		c = getchar();

		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			w = 1;
		} else {
			if (w != 0) {
				n++;
				w = 0;
			}
			if (c == '\n') {
				printf("%d\n", n);
				n = 0;
			}
			if (c == EOF) {
				if (n != 0) printf("%d\n", n);
				break;
			}
		}
	}

	return 0;
}
