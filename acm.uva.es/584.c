#include <stdio.h>
#include <string.h>
#include <ctype.h>

int rolls[1024], scores[1024], frame[1024], n;

int solve()
{
	int i, j, k, m;

	memset(scores, 0, sizeof(scores));

	for (i = 0, k = 10, j = 2, m = 0; i < n; i++) {
		frame[i] = m;

		if (rolls[i] <= 9) {
			scores[i] = rolls[i];
			k -= rolls[i];
			if (--j == 0) {
				k = 10;
				j = 2;
				m++;
			}
		} else {
			scores[i] = k;
			k = 10;
			j = 2;
			m++;
		}
	}

	for (k = 0, i = 0; i < n && frame[i] < 10; i++) {
		k += scores[i];
		if (rolls[i] == 'X')
			k += scores[i + 1] + scores[i + 2];
		else if (rolls[i] == '/')
			k += scores[i + 1];
	}

	return k;
}

int main()
{
	static char buf[65536];
	char *s;

	while (gets(buf) && buf[0] != 'G') {
		memset(rolls, 0, sizeof(rolls));

		for (s = buf, n = 0; *s; s++) {
			if (isdigit(*s))
				rolls[n++] = *s - '0';
			else if (*s == 'X' || *s == 'x')
				rolls[n++] = 'X';
			else if (*s == '/')
				rolls[n++] = '/';
		}

		printf("%d\n", solve());
	}

	return 0;
}
