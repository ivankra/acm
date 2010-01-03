#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char buf[128], *p, *q, *r;
	int i, s1, s2;

	while (fgets(buf, sizeof(buf), stdin)) {
		for (p = buf; *p == ' ' || *p == '\t'; p++);
		q = p;

		for (r = q; *r; r++);
		while (r > q && strchr(" \t\r\n", r[-1])) r--;

		for (i = 0, s1 = 0, s2 = 0; p < r; p++) {
			if (*p >= '0' && *p <= '9') {
				s2 += (s1 += *p - '0');
				i++;
			} else if (*p == 'X' && i == 9) {
				s2 += (s1 += 10);
				i++;
			} else if (*p != '-') {
				i = -1;
				break;
			}
		}

		while (q < r) putchar(*q++);
		printf(" is %s.\n",
			(i == 10 && ((s2 % 11) == 0)) ? "correct" : "incorrect"
		);
	}

	return 0;
}
