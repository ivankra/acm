#include <stdio.h>

int main()
{
	static int t, n, h, a[256];
	static char buf[256];
	register int i;

	scanf("%d", &t);

	while (t-- > 0 && scanf("%d %d", &n, &h) == 2) {
		h = n - h;

		for (i = 0, a[0] = -1; i >= 0;) {
			if (i == h) {
				for (i = 0; i < n; i++) buf[i] = '1';
				buf[i] = '\n';
				for (i = 0; i < h; i++) buf[a[i]] = '0';
				fwrite(buf, 1, n+1, stdout);
				i = h - 1;
			} else if (++a[i] < n) {
				a[i + 1] = a[i];
				i++;
			} else {
				i--;
			}
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}
