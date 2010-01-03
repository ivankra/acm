#include <stdio.h>

static int m[1024], r[16];

int main()
{
	static char buf[16384];
	static int t;
	int i, k, a, b, n;

	scanf("%d\n\n", &t);

	while (t-- > 0) {
		for (i = 0; i < 1024; i++) m[i] = 0;
		for (i = 0; i < 16; i++) r[i] = 0;

		for (i = 0; fgets(buf, sizeof(buf), stdin);) {
			for (k = 0; buf[k] && (buf[k] < '0' || buf[k] > '9');)
				k++;

			if (buf[k] == 0)
				break;

			for (;; i++) {
				while (buf[k] && (buf[k] < '0' || buf[k] > '9'))
					k++;

				if (buf[k] == 0)
					break;

				for (m[i] = 0; buf[k] >= '0' && buf[k] <= '9';)
					m[i] = m[i] * 10 + buf[k++] - '0';

				if (m[i] >= 1000)
					m[i] %= 1000;
			}
		}

		for (n = 1, i = 0; i < 1000; n++) {
			k = m[i++];
			a = (k / 10) % 10;
			b = k % 10;
			k = k / 100;

			if (k == 1)
				break;
			else if (k == 2)
				r[a] = b;
			else if (k == 3) {
				r[a] += b;
				if (r[a] >= 1000) r[a] -= 1000;
			} else if (k == 4) {
				r[a] *= b;
				if (r[a] >= 1000) r[a] %= 1000;
			} else if (k == 5)
				r[a] = r[b];
			else if (k == 6) {
				r[a] += r[b];
				if (r[a] >= 1000) r[a] -= 1000;
			} else if (k == 7) {
				r[a] *= r[b];
				if (r[a] >= 1000) r[a] %= 1000;
			} else if (k == 8)
				r[a] = m[r[b]];
			else if (k == 9)
				m[r[b]] = r[a];
			else if (r[b] != 0)
				i = r[a];
		}

		printf((t == 0) ? "%d\n" : "%d\n\n", n);
	}

	return 0;
}
