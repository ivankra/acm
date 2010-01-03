#include <stdio.h>

int main()
{
	static int a[256][8], c[256], lwr[256], n;
	static char buf[4096];
	char *p;
	int i, j, k;

	for (i = 0; i < 256; i++)
		lwr[i] = ((i >= 'A' && i <= 'Z') ? (i - 'A' + 'a') :
			  ((i >= 'a' && i <= 'z') ? i : 0));

	for (;;) {
		for (n = 0; gets(buf) && buf[0] != 'e' && buf[0] != '#';) {
			for (i = 0; i < 5; i++)
				a[n][i] = 0;

			for (p = buf, k = 0; *p; p++) {
				if (lwr[*p] != 0) {
					k = lwr[*p];
					continue;
				}

				if (*p != '/')
					continue;

				for (p++; *p && lwr[*p] == 0; p++);

				if (*p == '\0')
					break;

				for (i = 0; i < 5; i++) {
					if ("roygb"[i] == k) {
						a[n][i] = lwr[*p];
						break;
					}
				}
			}

			for (i = 0; i < 5; i++)
				if (a[n][i] == 0) break;

			if (i == 5)
				n++;
		}

		if (n == 0 || buf[0] == '#')
			break;

		for (i = 0; i < n; i++) {
			for (j = 0, c[i] = 0; j < n; j++) {
				if (i == j) continue;
				for (k = 0; k < 5; k++)
					if (a[i][k] != a[j][k]) c[i]++;
			}
		}

		for (k = 0, i = 1; i < n; i++)
			if (c[i] < c[k]) k = i;

		printf("%d\n", k+1);
	}

	return 0;
}
