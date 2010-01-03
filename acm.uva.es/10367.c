#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

typedef long long num;

typedef struct {
	num p, q;
} frac;

frac A[2][4];

num gcd(num x, num y)
{
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	return (y == 0) ? x : gcd(y, x % y);
}

char *fmt(frac f)
{
	static char s[1024];
	num d;
	if (f.q < 0) f.q = -f.q, f.p = -f.p;
	d = gcd(f.p, f.q);
	f.p /= d;
	f.q /= d;
	sprintf(s, (f.q == 1) ? "%lld" : "%lld/%lld", f.p, f.q);
	return s;
}

frac sub(frac a, frac b, frac c)
{
	frac r;
	r.p = a.p * b.q * c.q - a.q * b.p * c.p;
	r.q = a.q * b.q * c.q;
	return r;
}

void solve()
{
	int i, j, r, c;
	frac t;

	for (r = c = 0; c < 2; c++) {
		for (i = r; i < 2 && A[i][c].p == 0; i++);
		if (i == 2) continue;

		for (j = 0; j < 3; j++)
			t = A[i][j], A[i][j] = A[r][j], A[r][j] = t;

		t = A[r][c];
		for (i = c + 1; i < 3; i++)
			A[r][i].p *= t.q, A[r][i].q *= t.p;
		A[r][c].p = A[r][c].q = 1;

		for (i = 0; i < 2; i++) {
			if (i == r) continue;

			t = A[i][c];
			for (j = c + 1; j < 3; j++)
				A[i][j] = sub(A[i][j], t, A[r][j]);
			A[i][c].p = 0;
			A[i][c].q = 1;
		}

		r++;
	}

	for (i = 0; i < 2; i++)
		if (A[i][0].p == 0 && A[i][1].p == 0 && A[i][2].p != 0) break;

	if (i < 2) {
		printf("don't know\n");
		printf("don't know\n");
		return;
	}

	if (A[0][0].p == 1 && A[0][1].p == 0)
		printf("%s\n", fmt(A[0][2]));
	else
		printf("don't know\n");

	if (A[0][0].p == 1 && A[1][1].p == 1)
		printf("%s\n", fmt(A[1][2]));
	else if (A[0][0].p == 0 && A[0][1].p == 1)
		printf("%s\n", fmt(A[0][2]));
	else
		printf("don't know\n");
}

void parse(char *s, frac x[])
{
	num c, side, sign;
	int i, j;

	for (i = j = 0; s[i]; i++)
		if (strchr("+-=0123456789xy", s[i]) != NULL) s[j++] = s[i];
	s[j] = '\0';

	x[0].p = x[1].p = x[2].p = 0;
	x[0].q = x[1].q = x[2].q = 1;

	for (side = 1; *s;) {
		if (*s == '=') {
			s++;
			side = -side;
			continue;
		}

		for (sign = 1; *s == '+' || *s == '-'; s++)
			if (*s == '-') sign = -sign;

		assert(*s != '\0');

		if (isdigit(*s)) {
			for (c = 0; *s && isdigit(*s); s++)
				c = c * 10 + (*s - '0');
			c *= sign;

			if (*s != 'x' && *s != 'y') {
				x[2].p -= side * c;
				continue;
			}
		} else {
			c = sign;
		}

		assert(*s == 'x' || *s == 'y');

		if (*s == 'x')
			x[0].p += side * c;
		else if (*s == 'y')
			x[1].p += side * c;
		s++;
	}
}

int main()
{
	char s[1024];
	int t;

	while (gets(s) && sscanf(s, "%d", &t) != 1);

	while (t-- > 0) {
		gets(s);
		parse(s, A[0]);

		gets(s);
		parse(s, A[1]);

		gets(s);

		solve();

		if (t) printf("\n");
	}

	return 0;
}
