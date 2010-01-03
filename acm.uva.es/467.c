#include <stdio.h>

static int tm[16], n;

static int solve()
{
	static int r[16], s[16];
	int i, k, t;

	for (i = 1, k = tm[0]; i < n; i++)
		if (tm[i] < k) k = tm[i];
	k -= 5;

	for (t = k, i = 0; i < n; i++) {
		r[i] = (tm[i] - 5) - k;
		if (r[i] == 0) {
			r[i] = 5;
			s[i] = 1;
		} else {
			s[i] = 0;
		}
	}

	while (t <= 3600) {
		for (i = 0; i < n; i++)
			if (s[i] != 0) break;
		if (i == n) return t;

		for (i = 1, k = r[0]; i < n; i++)
			if (r[i] < k) k = r[i];

		for (i = 0; i < n; i++) {
			if ((r[i] -= k) > 0)
				continue;

			if (s[i] == 0) {
				s[i] = 1;
				r[i] = 5;
			} else if (s[i] == 1) {
				s[i] = 2;
				r[i] = tm[i];
			} else {
				s[i] = 0;
				r[i] = tm[i] - 5;
			}
		}

		t += k;
	}

	return 3601;
}

int main()
{
	char buf[1024], *s;
	int t, r;

	for (t = 1; gets(buf);) {
		for (n = 0, s = buf;; n++) {
			while (*s && (*s < '0' || *s > '9')) s++;
			if (*s == '\0') break;

			for (tm[n] = 0; *s >= '0' && *s <= '9';)
				tm[n] = tm[n] * 10 + *s++ - '0';
		}

		if (n == 0)
			continue;

		r = solve();

		if (r > 3600)
			printf("Set %d is unable to synch after one hour.\n",
			       t++);
		else
			printf("Set %d synchs again at %d minute(s) and "
			       "%d second(s) after all turning green.\n",
			       t++, r / 60, r % 60);
	}

	return 0;
}
