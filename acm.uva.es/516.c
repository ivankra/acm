#include <stdio.h>

int main()
{
	static char buf[4096];
	static int b[32], e[32];
	char *p;
	int i, j, k, n;

	while (gets(buf)) {
		for (p = buf, n = 1, k = 0; *p;) {
			while (*p && (*p < '0' || *p > '9')) p++;
			if (*p == '\0') break;

			for (i = 0; *p >= '0' && *p <= '9'; p++)
				i = i * 10 + *p - '0';

			while (*p && (*p < '0' || *p > '9')) p++;
			for (j = 0; *p >= '0' && *p <= '9'; p++)
				j = j * 10 + *p - '0';

			while (j-- > 0)
				n *= i;
			k++;			
		}

		if (k == 0)
			break;

		n--;

		for (i = 2, k = 0; n > 1 && (i * i) <= n; i = (i == 2) ? 3 : (i + 1)) {
			if ((n % i) != 0) continue;
			b[k] = i;
			for (e[k] = 1, n /= i; n > 1 && (n % i) == 0; e[k]++, n /= i);
			k++;
		}

		if (n > 1) {
			b[k] = n;
			e[k++] = 1;
		}

		while (k-- > 0)
			printf((k == 0) ? "%d %d\n" : "%d %d ", b[k], e[k]);
	}

	return 0;
}
