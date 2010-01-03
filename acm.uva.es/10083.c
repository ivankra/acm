#include <stdio.h>
#include <string.h>
#include <math.h>

#define NLIMBS 16

typedef unsigned long u_int32_t;
typedef unsigned long long u_int64_t;

void set(u_int32_t x[], u_int32_t y)
{
	int i;
	for (x[0] = y, i = 1; i < NLIMBS; i++)
		x[i] = 0;
}

void mul(u_int32_t x[], u_int32_t y)
{
	int i;
	u_int64_t c;

	for (c = 0, i = 0; i < NLIMBS; i++, c >>= 32)
		x[i] = (u_int32_t)(c += (u_int64_t)x[i] * (u_int64_t)y);
}

void add(u_int32_t x[], u_int32_t y[])
{
	int i;
	u_int64_t c;

	for (c = 0, i = 0; i < NLIMBS; i++, c >>= 32)
		x[i] = (u_int32_t)(c += (u_int64_t)x[i] + (u_int64_t)y[i]);
}

void fmt(char s[], u_int32_t z[])
{
	static char t[256];
	u_int64_t r;
	int i, k;

	for (k = 0;;) {
		for (i = NLIMBS - 1; i >= 0 && z[i] == 0; i--);
		if (i < 0) break;

		for (r = 0; i >= 0; i--) {
			r = (r << 32) | (u_int64_t)z[i];
			z[i] = (u_int32_t)(r / 10LL);
			r %= 10LL;
		}

		t[k++] = '0' + (int)r;
	}

	for (i = 0; k-- > 0;)
		s[i++] = t[k];
	s[i] = '\0';
}

char *solve(int t, int a, int b)
{
	static u_int32_t r[NLIMBS], s[NLIMBS];
	static char buf[256];
	int i, j, n;

	if (t == 1 || a < b || (a % b) != 0)
		return NULL;

	if (t == 0 || a == b)
		return "1";

	n = a / b;
	if (((n - 1.) * b * log10(t)) > 102.)
		return NULL;

	set(r, 0);
	set(s, 1);

	for (i = 0;;) {
		add(r, s);

		if (++i >= n)
			break;

		for (j = 0; j < b; j++)
			mul(s, t);
	}

	fmt(buf, r);
	return (strlen(buf) >= 100) ? NULL : buf;
}

int main()
{
	int t, a, b;
	char *s;

	while (scanf("%d %d %d", &t, &a, &b) == 3) {
		printf("(%d^%d-1)/(%d^%d-1) ", t, a, t, b);

		if ((s = solve(t, a, b)) == NULL)
			printf("is not an integer with less than 100 digits.\n");
		else
			printf("%s\n", s);
	}

	return 0;
}
