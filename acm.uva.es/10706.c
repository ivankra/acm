#include <stdio.h>

unsigned s[32768], len[32768];

void mktab()
{
	int i, d, m;

	for (i = 1, s[0] = len[0] = d = 0, m = 1; i < 31270; i++) {
		if (i == m) {
			m *= 10;
			d++;
		}

		len[i] = d;
		s[i] = s[i - 1] + d;
	}
}

int main()
{
	int i, n, t;
	char buf[32];

	mktab();

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (i = 1; n > s[i]; n -= s[i++]);
		for (i = 1; n > len[i]; n -= len[i++]);

		sprintf(buf, "%d", i);
		printf("%c\n", buf[n - 1]);
	}

	return 0;
}
