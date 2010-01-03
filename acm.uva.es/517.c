#include <stdio.h>
#include <string.h>

int apply(int x, int n, int rule)
{
	int r, k, i;

	for (r = 0, i = n - 1; i >= 0; i--) {
		k = ((((x >> ((i + 2) % n)) & 1) << 2) |
		     (((x >> i) & 1) << 1) |
		     ((x >> ((i + n - 1) % n)) & 1));
		r = (r << 1) | ((rule >> k) & 1);
	}

	return r;
}

char *fmt(int x, int n)
{
	static char buf[1024];
	int i, j;

	for (i = 0; i < n; i++)
		buf[i] = ((x >> (n - i - 1)) & 1) ? 'b' : 'a';

	for (j = 0; j < n; j++, i++)
		buf[i] = buf[j];

	for (j = 0, i = 1; i < n; i++) {
		if (memcmp(&buf[i], &buf[j], n) < 0)
			j = i;
	}

	buf[j + n] = '\0';

	return &buf[j];
}

int main()
{
	static int pat[65536+1024], iter[65536];
	int i, j, k, c, n, s, rule;

	while (scanf("%d", &n) == 1) {
		for (i = 0, pat[0] = 0; i < n && (c = getchar()) != EOF;) {
			if (c == 'a' || c == 'b') {
				pat[0] = (pat[0] << 1) | (c - 'a');
				i++;
			}
		}

		for (rule = 0, i = 0; i < 8; i++) {
			for (j = k = 0; j < 4 && (c = getchar()) != EOF;) {
				if (c == 'a' || c == 'b') {
					k = (k << 1) | (c - 'a');
					j++;
				}
			}

			if ((k & 1) == 0)
				continue;

			rule |= (1 << (k >> 1));
		}

		scanf("%d", &s);

		for (k = (1 << n), i = 0; i < k; i++)
			iter[i] = -1;
		iter[pat[0]] = 0;

		for (i = 1; i <= s; i++) {
			pat[i] = apply(pat[i - 1], n, rule);
			if (iter[pat[i]] >= 0)
				break;
			iter[pat[i]] = i;
		}

		if (i > s) {
			printf("%s\n", fmt(pat[s], n));
		} else {
			k = i - iter[pat[i]];
			k = pat[iter[pat[i]] + ((s - i) % k)];
			printf("%s\n", fmt(k, n));
		}
	}

	return 0;
}
