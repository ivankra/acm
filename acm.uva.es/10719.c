#include <stdio.h>

int main()
{
	static char buf[262144];
	static int isdig[256], isdigsz[256];
	char *s;
	int a, k, n, r;

	for (k = 0; k < 256; k++)
		isdig[k] = (k >= '0' && k <= '9');

	for (k = 0; k < 256; k++)
		isdigsz[k] = isdig[k] || (k == '-' || k == '\0');

	while (scanf("%d\n ", &k) == 1 && gets(buf)) {
		printf("q(x):");

		for (s = buf, r = 0, n = 0;;) {
			while (*s && !isdigsz[*s]) s++;
			if (*s == '\0') break;

			if (*s == '-') {
				for (s++, a = 0; isdig[*s]; s++)
					a = a * 10 + *s - '0';
				a = -a;
			} else {
				for (a = 0; isdig[*s]; s++)
					a = a * 10 + *s - '0';
			}

			if (n++ != 0)
				printf(" %d", r);

			r = r * k + a;
		}

		printf("\nr = %d\n\n", r);
	}

	return 0;
}
