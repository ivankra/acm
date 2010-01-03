#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *sym[] = {
	"0000.00.00.0000", ".0..0..0..0..0.", "000..00000..000",
	"000..0000..0000", "0.00.0000..0..0", "0000..000..0000",
	"0..0..0000.0000", "000..0..0..0..0", "0000.00000.0000",
	"0000.0000..0..0", ".0..0.000.0..0.", "......000......",
	"0.00.0.0.0.00.0", ".0....000....0."
};

char *tokp;
int tok, tokn;

int next()
{
	for (;;) {
		if (*tokp == '\0') return (tok = 0);

		if (isdigit(*tokp)) {
			for (tokn = 0; isdigit(*tokp);)
				tokn = tokn * 10 + *tokp++ - '0';
			return (tok = 'n');
		}

		return (tok = *tokp++);
	}
}

int take(char *s)
{
	static char in[5][256], buf[1024];
	int i, j, k;

	for (i = 0; i < 5; i++) {
		if (gets(buf) == NULL) return 0;

		for (j = k = 0; buf[j]; j++)
			if (buf[j] == '.' || buf[j] == '0') in[i][k++] = buf[j];
		in[i][k] = in[i][k+1] = in[i][k+2] = '\0';
	}

	for (k = 0; in[0][3 * k + 2]; k++) {
		for (i = 0; i < 14; i++) {
			for (j = 0; j < 15; j++)
				if (sym[i][j] != in[j / 3][3 * k + (j % 3)]) break;
			if (j >= 15) break;
		}

		if (i < 14)
			*s++ = "0123456789+-*/"[i];
	}

	gets(buf);

	*s = '\0';
	return 1;
}

int term()
{
	int r = tokn;

	for (next();;) {
		if (tok == '*') {
			next();
			r *= tokn;
			next();
		} else if (tok == '/') {
			next();
			r /= tokn;
			next();
		} else {
			return r;
		}
	}
}

int eval()
{
	int r = term();

	for (;;) {
		if (tok == '+') {
			next();
			r += term();
		} else if (tok == '-') {
			next();
			r -= term();
		} else {
			return r;
		}
	}
}

void print(char *s)
{
	int i, j, r, n = strlen(s);

	for (r = 0; r < 5; r++) {
		for (i = 0; i < n; i++) {
			j = (s[i] == '-') ? 11 : (s[i] - '0');
			printf(i ? " %.3s" : "%.3s", &sym[j][r * 3]);
		}
		printf("\n");
	}

	printf("\n");
}

int main()
{
	static char s[256], t[256];

	while (take(s) && strcmp(s, "0") != 0) {
		tokp = s;
		next();

		sprintf(t, "%d", eval());
		print(t);
	}

	return 0;
}
