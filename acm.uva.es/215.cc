#include <cstdio>
#include <cstring>
#include <cctype>

int nrows, ncols, ok[32][32], val[32][32];
char expr[32][16][128];

int eval(int r, int c) {
	if (ok[r][c] > 0) return 1;
	if (ok[r][c] < 0) return 0;
	ok[r][c] = -1;

	val[r][c] = 0;
	for (char *s = expr[r][c]; *s;) {
		int sign = 1;

		for (; *s && !isdigit(*s) && !isalpha(*s); s++)
			if (*s == '-') sign *= -1;
		if (*s == 0) break;

		if (isdigit(*s)) {
			int x, p=0;
			if (sscanf(s, "%d%n", &x, &p) < 1 || p <= 0) break;
			s += p;
			val[r][c] += sign * x;
		} else {
			int r1 = toupper(*s++) - 'A', c1, p=0;
			if (sscanf(s, "%d%n", &c1, &p) < 1 || p <= 0) break;
			s += p;
			if (r1 < 0 || r1 >= nrows || c1 < 0 || c1 >= ncols) return 0;
			if (!eval(r1,c1)) return 0;
			val[r][c] += sign * val[r1][c1];
		}
	}

	ok[r][c] = 1;
	return 1;
}

int main() {
	while (scanf("%d %d", &nrows, &ncols) == 2 && nrows > 0 && ncols > 0) {
		int c;
		while ((c = getchar()) != EOF && c != '\n');

		for (int r = 0; r < nrows; r++)
		for (int c = 0; c < ncols; c++)
			gets(expr[r][c]);

		memset(ok, 0, sizeof(ok));
		int m = 0;
		for (int r = 0; r < nrows; r++)
		for (int c = 0; c < ncols; c++)
			if (ok[r][c] == 0 && !eval(r,c)) m++;

		if (m != 0) {
			for (int r = 0; r < nrows; r++)
			for (int c = 0; c < ncols; c++)
				if (ok[r][c] < 0)
					printf("%c%d: %s\n", 'A'+r, c, expr[r][c]);
			printf("\n");
			continue;
		}

		printf(" ");
		for (int c = 0; c < ncols; c++)
			printf("%6d", c);
		printf("\n");

		for (int r = 0; r < nrows; r++) {
			printf("%c", r+'A');
			for (int c = 0; c < ncols; c++)
				printf("%6d", val[r][c]);
			printf("\n");
		}

		printf("\n");
	}
}
