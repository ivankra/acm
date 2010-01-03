#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int op[32], term[32], where[32], result[32], n, m, sum;

int solve()
{
	static int a[32], c[32];
	int i, j, s;

	where[0] = 'L';
	for (i = 1; op[i - 1] != '='; i++)
		where[i] = (op[i - 1] == '-') ? 'R' : 'L';

	where[i++] = 'R';
	for (; i < n; i++)
		where[i] = (op[i - 1] == '-') ? 'L' : 'R';

	for (i = 0, m = 0; i < n; i++)
		if (where[i] == 'L') m++;

	for (i = 0, s = 0; i < m; i++)
		s += term[a[i] = m - 1 - i];

	while (2 * s != sum) {
		for (i = m - 1; i > 0; i--) {
			s -= term[a[i]];

			if (++a[i] < a[i - 1]) {
				s += term[a[i]];
				break;
			}

			s += term[a[i] = m - 1 - i];
		}

		if (i == 0) {
			if (a[i] == (n - 1)) return 1;
			s -= term[a[i]];
			s += term[++a[i]];
		}
	}

	for (i = 0, j = 0; i < n; i++)
		if (where[i] == 'L') result[i] = term[a[j++]];

	memset(c, 0, sizeof(c));
	for (i = 0; i < m; i++)
		c[a[i]] = 1;

	for (i = j = 0; i < n; i++) {
		if (where[i] == 'R') {
			while (c[j]) j++;
			result[i] = term[j++];
		}
	}

	printf("%d", result[0]);
	for (i = 1; i < n; i++)
		printf(" %c %d", op[i - 1], result[i]);
	printf("\n");

	return 0;
}

void parse(char *s)
{
	for (sum = 0, n = 0;;) {
		while (*s && !isdigit(*s)) s++;
		if (*s == '\0') break;

		for (term[n] = 0; *s && isdigit(*s); s++)
			term[n] = term[n] * 10 + *s - '0';
		sum += term[n];

		while (*s && strchr("+-=", *s) == NULL) s++;
		if (*s != '\0')
			op[n] = *s++;

		n++;
	}
}

int main()
{
	static char s[65536];

	while (gets(s)) {
		parse(s);
		if (solve()) printf("no solution\n");
	}

	return 0;
}
