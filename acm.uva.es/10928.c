#include <stdio.h>
#include <ctype.h>

int main()
{
	static char buf[131072];
	char *p;
	int a[1024], i, j, k, n, T;

	while (gets(buf) && sscanf(buf, "%d", &T) != 1);

	while (T-- > 0) {
		while (gets(buf) && sscanf(buf, "%d", &n) != 1);

		for (i = 0; i < n && gets(buf); i++) {
			for (p = buf, a[i] = 0;;) {
				while (*p && !isdigit(*p)) p++;
				if (*p == 0) break;
				a[i]++;
				while (*p && isdigit(*p)) p++;
			}
		}

		for (i = 0, j = a[0]; i < n; i++)
			if (a[i] < j) j = a[i];

		for (i = k = 0; i < n; i++)
			if (a[i] == j) printf(k++ ? " %d" : "%d", i+1);
		printf("\n");
	}

	return 0;
}
