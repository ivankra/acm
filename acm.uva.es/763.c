#include <stdio.h>

#define MAXN 112

int main()
{
	static char s1[1024], s2[1024];
	static int t, r[MAXN], dirty;
	register int i, k;
	register char *p;

	for (t = 0; scanf(" %[01] %[01]", s1, s2) == 2; t++) {
		for (p = s1; *p; p++);
		for (i = 0, p--; p >= s1;) r[i++] = *p-- - '0';
		while (i < MAXN) r[i++] = 0;

		for (p = s2; *p; p++);
		for (i = 0, p--; p >= s2;) r[i++] += *p-- - '0';

		for (;;) {
			for (i = 1; i < MAXN; i++) {
				if (r[i] > 0 && r[i - 1] > 0) {
					k = (r[i] < r[i-1]) ? r[i] : r[i-1];
					r[i - 1] -= k;
					r[i] -= k;
					r[i + 1] += k;
				}
			}

			k = (r[1] << 1) + r[0];
			if (r[0] > 1 || k > 2) {
				r[2] += k / 3;
				k %= 3;
				r[0] = k & 1;
				r[1] = k >> 1;
				dirty = 1;
			} else {
				dirty = 0;
			}

			for (i = 2; i < MAXN; i++)
				if (r[i] > 1) break;

			if (i >= MAXN && !dirty)
				break;

			for (; i < MAXN; i++) {
				if (r[i] > 1) {
					r[i + 1] += r[i] >> 1;
					r[i - 2] += r[i] >> 1;
					r[i] &= 1;
				}
			}
		}

		p = s1;
		if (t > 0) *p++ = '\n';

		for (i = MAXN - 1; i >= 1 && r[i] == 0; i--);

		while (i >= 0)
			*p++ = r[i--] + '0';
		*p++ = '\n';

		fwrite(s1, 1, p - s1, stdout);
	}

	return 0;
}
