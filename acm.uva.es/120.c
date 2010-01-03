#include <stdio.h>

int main()
{
	static char buf[1024];
	static int a[1024], s[1024], n;
	char *p;
	int i, j, k, r;

	while (gets(buf)) {
		for (n = 0, p = buf;;) {
			while (*p && (*p < '0' || *p > '9')) p++;

			if (*p == '\0')
				break;

			for (a[n] = 0; *p >= '0' && *p <= '9';)
				a[n] = a[n] * 10 + *p++ - '0';

			n++;
		}

		if (n == 0)
			continue;

		printf("%s\n", buf);

		/* Sort a[] to s[] */
		for (s[0] = a[0], i = 1; i < n; i++) {
			for (k = a[i], j = i - 1; j >= 0 && s[j] > k; j--)
				s[j + 1] = s[j];
			s[j + 1] = k;
		}

		for (r = n; r > 0;) {
			/* r: number of unsorted elements at the top */

			while (r > 0 && a[r - 1] == s[r - 1])
				r--;

			if (r == 0)
				break;

			/* find which element must be put now at the bottom */
			for (k = s[r - 1], i = 0; i < r; i++)
				if (a[i] == k) break;

			/* if it's not at the top, move it to the top */
			if (i != 0) {
				printf("%d ", n - i);
				for (j = 0; j < i;) {
					k = a[j];
					a[j++] = a[i];
					a[i--] = k;
				}

				continue;  /* (in case this has decreased r) */
			}

			/* move the element to its proper place */
			printf("%d ", n - (r - 1));
			for (j = 0, i = r - 1; j < i;) {
				k = a[j];
				a[j++] = a[i];
				a[i--] = k;
			}
		}

		printf("0\n");
	}

	return 0;
}
