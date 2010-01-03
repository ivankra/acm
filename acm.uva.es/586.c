#include <stdio.h>
#include <string.h>

static int tok, tok_num;

static int next(void)
{
	register int c;

	for (tok_num = 0;;) {
		c = getchar();

		if (c == EOF) return (tok = 0);
		if (c == ' ' || c == '\t' || c == '\r' || c == '\n') continue;

		if (c >= '0' && c <= '9') {
			for (; c >= '0' && c <= '9'; c = getchar())
				tok_num = tok_num * 10 + c - '0';
			if (c != EOF) ungetc(c, stdin);
			return (tok = 'F');
		}

		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			tok = (c >= 'A' && c <= 'Z') ? c : (c - 'a' + 'A');

			while ((c = getchar()) != EOF)
				if (!((c >= 'A' && c <= 'Z') ||
				      (c >= 'a' && c <= 'z')))
					break;
			if (c != EOF) ungetc(c, stdin);

			if (tok != 'B' && tok != 'E' && tok != 'L' &&
			    tok != 'O')
				return (tok = 'N');
			else
				return tok;
		}
	}
}

#define MAXDEG 16
#define MAXBLK 32

int main()
{
	static int t, nr_tests, lev, j;
	static struct { int p[MAXDEG], k; } st[MAXBLK];
	register int i;

	next();
	nr_tests = tok_num;

	next();

	for (t = 1; t <= nr_tests; t++) {
		for (i = 0; i < MAXDEG; i++)
			st[0].p[i] = 0;
		lev = 0;

		do {
			if (tok == 'B' || tok == 'L') {
				for (lev++, i = 0; i < MAXDEG; i++)
					st[lev].p[i] = 0;

				if (tok == 'B') {
					next();
					st[lev].k = 1;
				} else if (tok == 'L') {
					next();
					st[lev].k = (tok=='F') ? tok_num : -1;
					next();
				}
			} else if (tok == 'O') {
				next();
				if (tok == 'F') {
					st[lev].p[0] += tok_num;
					next();
				}
			} else if (tok == 'E') {
				next();

				if (lev == 0) continue;

				if (st[lev].k >= 2) {
					for (i = 0; i < MAXDEG; i++)
						st[lev].p[i] *= st[lev].k;
				} else if (st[lev].k == 0) {
					for (i = 0; i < MAXDEG; i++)
						st[lev].p[i] = 0;
				} else if (st[lev].k < 0) {
					for (i = MAXDEG - 2; i >= 0; i--)
						st[lev].p[i+1] = st[lev].p[i];
					st[lev].p[0] = 0;
				}

				lev--;
				for (i = 0; i < MAXDEG; i++)
					st[lev].p[i] += st[lev+1].p[i];
			}
		} while (lev > 0);

		printf("Program #%d\nRuntime = ", t);

		for (j = 0, i = MAXDEG - 1; i >= 1; i--) {
			if (st[0].p[i] == 0)
				continue;

			if (st[0].p[i] != 1)
				printf((j==0) ? "%d*n" : "+%d*n", st[0].p[i]);
			else
				printf((j==0) ? "n" : "+n");

			if (i > 1)
				printf("^%d", i);

			j = 1;
		}

		if (j == 0)
			printf("%d", st[0].p[0]);
		else if (st[0].p[0] != 0)
			printf("+%d", st[0].p[0]);

		printf("\n\n");
	}

	return 0;
}
