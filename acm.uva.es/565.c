#include <stdio.h>
#include <string.h>
#include <ctype.h>

int P[2][32], U, w[32], n, k, G;

int f(int X, int S, int p)
{
	for (;;) {
		p = w[p];
		if (p >= 16) {
			if (S == G) {
				printf("Toppings: ");
				for (p = 0; p < 16; p++)
					if ((X >> p) & 1) printf("%c", p + 'A');
				printf("\n");
				return 1;
			}
			return 0;
		}

		if (f(X, S | P[0][p], p + 1)) return 1;
		X |= 1 << p;
		S |= P[1][p];
		p++;
	}
}

int main()
{
	int c, i, j, s;

	for (;;) {
		memset(P, 0, sizeof(P));
		for (n = 0;;) {
			while ((c = getchar()) != EOF && strchr("+-;.", c) == NULL);
			if (c == EOF || c == '.') break;

			if (c == ';') {
				n++;
			} else if (c == '+') {
				while ((c = getchar()) != EOF && !isalpha(c));
				P[1][toupper(c) - 'A'] |= 1 << n;
			} else if (c == '-') {
				while ((c = getchar()) != EOF && !isalpha(c));
				P[0][toupper(c) - 'A'] |= 1 << n;
			}
		}

		if (n == 0)
			break;

		G = (1 << n) - 1;

		for (U = c = s = 0, i = j = 0; i < 16; i++) {
			if (P[0][i] == 0 && P[1][i] == 0)
				continue;
			if (P[1][i] == 0) {
				s |= P[0][i];
			} else if (P[0][i] == 0) {
				s |= P[1][i];
				c |= 1 << i;
			} else {
				U |= 1 << i;
			}
		}

		for (i = 0; i <= 16; i++) {
			for (j = i; j < 16 && ((U >> j) & 1) == 0; j++);
			w[i] = j;
		}

		if (f(c, s, 0) == 0)
			printf("No pizza can satisfy these requests.\n");
	}

	return 0;
}
