#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Matrix {
	int a[64][64], d;
};

void mmul(Matrix &A, Matrix &B)
{
	static int t[64][64];

	for (int i = 0; i < A.d; i++)
		for (int j = 0; j < A.d; j++) {
			t[i][j] = 0;
			for (int k = 0; k < A.d; k++) {
				t[i][j] += A.a[i][k] * B.a[k][j];
				t[i][j] %= 4242;
			}
		}

	for (int i = 0; i < A.d; i++)
		for (int j = 0; j < A.d; j++)
			A.a[i][j] = t[i][j];		
}

void mpow(Matrix &r, int n)
{
	static Matrix m;
	int i, j;

	memcpy(&m, &r, sizeof(Matrix));
	memset(&r, 0, sizeof(r));
	r.d = m.d;
	for (int i = 0; i < r.d; i++)
		r.a[i][i] = 1;

	for (; n > 0; n >>= 1) {
		if (n & 1) mmul(r, m);
		mmul(m, m);
	}
}

int main()
{
	int i, j, n, c, fb[8], T;
	Matrix m;
	char s[16384];

	for (scanf("%d", &T); T-- > 0 && scanf("%d %d %s", &n, &c, s) == 3;) {
		for (i = 0; s[i]; i++)
			s[i] = toupper(s[i]);

		memset(fb, 0, sizeof(fb));
		for (i = 'A'; i <= 'A'+c; i++) {
			char *p = strchr(s, i);
			if (p != NULL)
				for (p++; *p; p++) fb[i-'A'] |= 1 << (*p-'A');
		}

		memset(&m, 0, sizeof(m));
		m.d = 1 << c;
		for (int s = 0; s < m.d; s++)
			for (int a = 0; a < c; a++)
				if (s & (1 << a)) m.a[s][s & ~fb[a]]++;

		mpow(m, n);

		for (i = j = 0; i < m.d; i++)
			j = (j + m.a[m.d-1][i]) % 4242;

		printf("%d\n", j);
	}

	return 0;
}
