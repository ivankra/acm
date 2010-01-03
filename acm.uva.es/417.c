#include <stdio.h>

#define MAXWORDS 83681

static char words[MAXWORDS][6], wlen[MAXWORDS];

int main()
{
	static char buf[16];
	register int i, k, n, a, b;
	char *p;

	for (k = 1, n = 0; k < 6; k++) {
		for (i = 0, buf[0] = 0; i >= 0;) {
			if (i == k) {
				wlen[n] = k;
				for (i = 0; i < k; i++)
					words[n][i] = buf[i];
				i = k - 1;
				n++;
			} else if (buf[i] == 'z') {
				i--;
			} else {
				if (buf[i] == 0)
					buf[i] = 'a';
				else
					buf[i]++;
				buf[i+1] = buf[i];
				i++;
			}
		}
	}

	while (scanf(" %14[a-z]", buf) == 1 && buf[0] != '\0') {
		for (n = 0; buf[n]; n++);

		for (a = 0, b = MAXWORDS - 1; a < b;) {
			i = (a + b) >> 1;

			if (wlen[i] < n) {
				a = i + 1;
				continue;
			} else if (wlen[i] > n) {
				b = i - 1;
				continue;
			}

			for (p = words[i], k = 0; k < n; k++, p++)
				if (buf[k] != *p) break;

			if (k == n)
				a = b = i;
			else if (buf[k] > *p)
				a = i + 1;
			else
				b = i - 1;
		}

		if (wlen[a] != n) {
			printf("0\n");
			continue;
		}

		for (i = 0, p = words[a]; i < n; i++)
			if (buf[i] != *p++) break;

		if (i < n)
			printf("0\n");
		else
			printf("%d\n", 1+a);
	}

	return 0;
}

