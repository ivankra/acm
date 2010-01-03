#include <stdio.h>
#include <string.h>

#define NLIMBS 4

typedef struct {
	unsigned a[NLIMBS];
} num_t;

int cwidth, gtab[64][64][64][4];
num_t ftab[64][64][64][4], zero, one;

void set(num_t *z, unsigned a)
{
	unsigned i;

	z->a[0] = a;
	for (i = 1; i < NLIMBS; i++)
		z->a[i] = 0;
}

void add(num_t *z, num_t *x)
{
	unsigned i, c;

	for (c = 0, i = 0; i < NLIMBS; i++, c >>= 31)
		z->a[i] = (c += z->a[i] + x->a[i]) & 0x7FFFFFFF;
}

unsigned div(num_t *z, unsigned d)
{
	unsigned long long r;
	int i;

	for (i = NLIMBS - 1, r = 0; i >= 0; i--) {
		r = (r << 31) | (unsigned long long)z->a[i];
		z->a[i] = (unsigned)(r / (unsigned long long)d);
		r %= (unsigned long long)d;
	}

	return (unsigned)r;
}

int iszero(num_t *z)
{
	int i;
	for (i = 0; i < NLIMBS; i++)
		if (z->a[i] != 0) return 0;
	return 1;
}

char *print(num_t *z)
{
	static char s[1024], r[1024];
	static num_t t;
	char *p, *q;

	memcpy(&t, z, sizeof(num_t));

	for (p = s; p == s || !iszero(&t);)
		*p++ = '0' + div(&t, 10);

	for (q = r; p-- > s;) *q++ = *p;
	*q = '\0';

	return r;
}

num_t *count(int l, int r, int h, int sl, int sr)
{
	int x, y;
	num_t *z;

	if (l >= r)
		return &zero;

	if (l == 0 && sl < 0) sl = 1;
	if (r == cwidth && sr > 0) sr = -1;

	if (h == 0)
		return (sl > 0 && sr < 0) ? &one : &zero;

	x = (sl + 1) | ((sr + 1) >> 1);
	z = &ftab[l][r][h][x];
	if (gtab[l][r][h][x])
		return z;
	gtab[l][r][h][x] = 1;

	set(z, 0);
	for (x = l; 0 <= x && x < r; x += sl)
		for (y = r; x < y && l < y && y <= cwidth; y += sr)
			add(z, count(x, y, h - 1, sl, sr));

	return z;
}

num_t *count_rect(int w, int h)
{
	static num_t z;
	int x, y;

	memset(gtab, 0, sizeof(gtab));

	cwidth = w;

	set(&z, 0);
	for (x = 0; x <= cwidth; x++)
		for (y = x + 1; y <= cwidth; y++)
			add(&z, count(x, y, h - 1, -1, +1));

printf("%dx%d => %s\n",w,h,print(&z));

	return &z;
}

num_t *solve(int n)
{
	static num_t z;
	int a, b;
	num_t *y;

printf("solve(n=%d)\n", n);

	if ((n & 1) != 0)
		return &zero;

	set(&z, 0);
        for (a = 1; a <= n; a++) {
		b = n / 2 - a;
		if (b < a) break;

		y = count_rect(a, b);
		add(&z, y);
		if (a != b) add(&z, y);
	}

	return &z;
}

int main()
{
	int n, t;

	set(&zero, 0);
	set(&one, 1);

	for (t = 1; scanf("%d", &n) == 1; t++) {
		printf("Case #%d: %s\n", t, print(solve(n)));
	}

	return 0;
}
