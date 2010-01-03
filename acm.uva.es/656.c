#include <stdio.h>

static int code[16], m;

static int check(int x, int y)
{
	static int s[256];
	register int i, k;

	s[0] = x;
	k = 0;

	for (i = 0; i < m; i++) {
		if (code[i] == 2) {
			s[k + 1] = s[k];
			k++;
			continue;
		}

		if (k-- < 1)
			return i;

		if (code[i] == 0) {
			s[k] += s[k + 1];
			if (s[k] < -30000 || s[k] > 30000) return i;
		} else if (code[i] == 1) {
			if (s[k + 1] == 0) return i;
			s[k] /= s[k + 1];
		} else if (code[i] == 3) {
			s[k] *= s[k + 1];
			if (s[k] < -30000 || s[k] > 30000) return i;
		} else {
			s[k] -= s[k + 1];
			if (s[k] < -30000 || s[k] > 30000) return i;
		}
	}

	return (k == 0 && s[0] == y) ? m : (m - 1);
}

int main()
{
	static char *str[] = { "ADD", "DIV", "DUP", "MUL", "SUB" };
	static int t, n, x[256], y[256], found;
	int i, k;

	for (t = 1; scanf("%d", &n) == 1 && n > 0; t++) {
		for (i = 0; i < n; i++) scanf("%d", &x[i]);
		for (i = 0; i < n; i++) scanf("%d", &y[i]);

		for (m = 0, found = 0; m <= 10; m++) {
			for (i = 0; i < m; i++)
				code[i] = 0;

			for (;;) {
				for (i = 0; i < n; i++)
					if ((k = check(x[i], y[i])) < m) break;

				if (i >= n) {
					found = 1;
					break;
				}

				for (i = k + 1; i < m; i++)
					code[i] = 0;

				for (i = k;;) {
					if (++code[i] < 5)
						break;

					code[i--] = 0;
					if (i < 0) break;
				}

				if (i < 0)
					break;
			}

			if (found)
				break;
		}

		if (!found) {
			printf("Program %d\nImpossible\n\n", t);
		} else if (m == 0) {
			printf("Program %d\nEmpty sequence\n\n", t);
		} else {
			printf("Program %d\n%s", t, str[code[0]]);
			for (i = 1; i < m; i++)
				printf(" %s", str[code[i]]);
			printf("\n\n");
		}
	}

	return 0;
}
