#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define EPS 1e-9

int tok, tokid, toknum, n;
double A[32][32];

void reduce()
{
	int i, j, k, r, c;
	double t;

	for (r = c = 0; c < n; c++) {
		for (i = 0; i < n; i++)
			if (fabs(A[i][c]) < EPS) A[i][c] = 0.;

		for (i = k = r; i < n; i++)
			if (fabs(A[i][c]) > fabs(A[k][c])) k = i;

		if (fabs(A[k][c]) < EPS)
			continue;

		if (k != r) {
			for (i = 0; i <= n; i++) {
				t = A[k][i];
				A[k][i] = A[r][i];
				A[r][i] = t;
			}
		}

		for (i = 0; i < c; i++)
			A[r][i] = 0.;
		for (i = c + 1; i <= n; i++)
			A[r][i] /= A[r][c];
		A[r][c] = 1.;

		for (i = 0; i < n; i++) {
			if (i == r)
				continue;

			if (fabs(A[i][c]) < EPS) {
				A[i][c] = 0.;
				continue;
			}

			for (j = c + 1; j <= n; j++)
				A[i][j] -= A[i][c] * A[r][j];
			A[i][c] = 0.;
		}

		r++;
	}
}

int next()
{
	int c;

	for (;;) {
		while ((c = getchar()) != EOF && isspace(c));

		if (c == EOF)
			return (tok = EOF);

		if (c == '(' || c == ')')
			return (tok = c);

		if (isdigit(c) || c == '-') {
			ungetc(c, stdin);
			scanf("%d", &toknum);
			return (tok = 'n');
		}

		if (isalpha(c)) {
			tokid = tolower(c) - 'a';
			return (tok = 'a');
		}
	}
}

void tree(double r[])
{
	double s[32];
	int i, k;

	for (i = 0; i <= n; i++)
		s[i] = 0.;

	assert(tok == '(');
	next();

	for (k = 0; tok != ')'; k++) {
		if (tok == 'n') {
			s[n] += (double)toknum;
			next();
		} else if (tok == 'a') {
			assert(tokid < n);
			s[tokid] += 1.;
			next();
		} else {
			tree(s);
		}
	}

	next();

	for (i = 0; i <= n; i++)
		r[i] += s[i] / (double)k;
}

int main()
{
	double x[32];
	int d[32], i, j, k, t;

	for (next(), t = 1; tok == 'n' && toknum > 0; t++) {
		n = toknum;
		next();

		for (i = 0; i <= n; i++)
			for (j = 0; j <= n; j++)
				A[i][j] = 0.;

		for (i = 0; i < n; i++) {
			assert(tok == 'a');
			j = tokid;
			next();
			tree(A[j]);
			A[j][j] -= 1.;
			A[j][n] = -A[j][n];
		}

		reduce();

		memset(d, 0, sizeof(d));
		for (i = 0; i < n; i++) {
			for (j = 0; j < n && fabs(A[i][j]) < EPS; j++);
			if (j == n) break;

			if (fabs(A[i][j] - 1.) > EPS) continue;

			for (k = j + 1; k < n && fabs(A[i][k]) < EPS; k++);
			if (k < n) continue;

			d[j] = 1;
			x[j] = A[i][n];
		}

		printf("Game %d\n", t);
		for (i = 0; i < n; i++) {
			printf("Expected score for %c ", i + 'a');
			if (d[i])
				printf("= %.3f\n", x[i]);
			else
				printf("undefined\n");
		}
		printf("\n");
	}

	return 0;
}
