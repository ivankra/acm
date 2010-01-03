#include <stdio.h>

int main()
{
	static char buf[65536];
	int i, c;
	long long a, b, r;

	while (gets(buf)) {
		printf("%s\n", buf);

		for (i = 0; buf[i] && (buf[i] < '0' || buf[i] > '9'); i++);

		for (a = 0; a <= 0x7FFFFFFF && buf[i] >= '0' && buf[i] <= '9';)
			a = a * 10 + buf[i++] - '0';

		if (a > 0x7FFFFFFF)
			printf("first number too big\n");

		while (buf[i] && buf[i] != '+' && buf[i] != '*') i++;
		c = buf[i++];

		while (buf[i] && (buf[i] < '0' || buf[i] > '9')) i++;

		for (b = 0; b <= 0x7FFFFFFF && buf[i] >= '0' && buf[i] <= '9';)
			b = b * 10 + buf[i++] - '0';

		if (b > 0x7FFFFFFF)
			printf("second number too big\n");

		if (c == '*' && (a == 0 || b == 0))
			continue;

		if (a > 0x7FFFFFFF || b > 0x7FFFFFFF) {
			printf("result too big\n");
			continue;
		}

		r = (c == '+') ? (a + b) : (a * b);

		if (r > 0x7FFFFFFF)
			printf("result too big\n");
	}

	return 0;
}
