#include <stdio.h>

#define NLIMBS 4
typedef unsigned long limb_t;
typedef unsigned long long xlimb_t;

static void iadd(limb_t *z, const limb_t *x, const limb_t *y)
{
	register xlimb_t c;
	register int i;
	for (i = 0, c = 0; i < NLIMBS; i++, c >>= 32) {
		c += (xlimb_t)x[i] + (xlimb_t)y[i];
		z[i] = c & 0xFFFFFFFF;
	}
}

static void isub(limb_t *z, const limb_t *x, const limb_t *y)
{
	register xlimb_t c;
	register int i;
	for (i = 0, c = 1; i < NLIMBS; i++) {
		c += (xlimb_t)x[i] + (xlimb_t)((~y[i]) & 0xFFFFFFFF);
		z[i] = c & 0xFFFFFFFF;
		c = (c > 0xFFFFFFFF) ? 1 : 0;
	}
}

static void iadds(limb_t *x, unsigned k)
{
	register limb_t c;
	register int i;
	for (i = 0, c = k; i < NLIMBS; i++) {
		if ((c = c + x[i]) < x[i]) {
			x[i] = c;
			c = 1;
		} else {
			x[i] = c;
			break;
		}
	}
}

static void imuls(limb_t *z, const limb_t *x, unsigned k)
{
	register xlimb_t c;
	register int i;
	for (i = 0, c = 0; i < NLIMBS; i++, c >>= 32) {
		c += (xlimb_t)x[i] * k;
		z[i] = c & 0xFFFFFFFF;
	}
}

static unsigned idivs(limb_t *q, const limb_t *x, unsigned y)
{
	register unsigned long long c;
	register int i;
	for (i = NLIMBS - 1, c = 0; i >= 0; i--) {
		c = (c << 32) | x[i];
		if (q == NULL) {
			c %= y;
		} else {
			q[i] = c / y;
			c %= y;
		}
	}
	return (unsigned)c;
}

static int icmp(const limb_t *x, const limb_t *y)
{
	register int i;
	for (i = NLIMBS; i-- > 0;)
		if (x[i] != y[i]) return (x[i] > y[i]) ? 1 : -1;
	return 0;
}

static void iset(limb_t *x, const char *s)
{
	int i;

	for (i = 0; i < NLIMBS; i++)
		x[i] = 0;

	while (*s == '0') s++;

	for (i = 0; *s; s++, i++) {
		if (*s >= '0' && *s <= '9') {
			if (i > 0) imuls(x, x, 10);
			iadds(x, *s - '0');
		}
	}
}

static void iprint(limb_t *x)
{
	static char buf[256], buf2[256];
	static limb_t t[NLIMBS];
	int i, j, k;

	for (i = 0; i < NLIMBS; i++)
		t[i] = x[i];

	for (i = 0, k = 0;;) {
		for (j = 0; j < NLIMBS; j++)
			if (t[j] != 0) break;
		if (j >= NLIMBS && k > 0) break;

		if (k != 0 && (k % 3) == 0)
			buf[i++] = ',';

		buf[i++] = idivs(t, t, 10) + '0';
		k++;
	}

	for (j = 0; i-- > 0;)
		buf2[j++] = buf[i];
	buf2[j++] = '\n';
	fwrite(buf2, 1, j, stdout);
}

static limb_t pow26[23][NLIMBS];
static limb_t pow26_sums[23][NLIMBS];

static void giveword(const char *s)
{
	static limb_t x[NLIMBS], z[NLIMBS];
	static char buf[256], buf2[256];
	int i, j, len;

	iset(x, s);

	for (len = 1; icmp(pow26_sums[len], x) < 0; len++);
	isub(z, x, pow26_sums[len - 1]);

	for (i = 0;;) {
		for (j = 0; j < NLIMBS; j++) if (z[j]) break;
		if (j >= NLIMBS && i > 0) break;
		buf[i++] = idivs(z, z, 26) + 'a';
	}

	for (j = 0; i-- > 0;)
		buf2[j++] = buf[i];
	buf2[j] = '\0';

	printf("%-22s", buf2);
	iprint(x);
}

static void givenum(const char *s, int len)
{
	static limb_t x[NLIMBS];
	int i;

	iset(x, "0");

	for (i = 0; i < len; i++) {
		if (i >= 1)
			imuls(x, x, 26);

		if (s[i] >= 'a' && s[i] <= 'z')
			iadds(x, s[i] - 'a');
		else
			iadds(x, s[i] - 'A');
	}
	iadd(x, x, pow26_sums[len - 1]);

	printf("%-22s", s);
	iprint(x);
}

int main()
{
	static char buf[256];
	int i, c;

	for (i = 1, iset(pow26[0],"1"), iset(pow26_sums[0],"1"); i < 23; i++) {
		imuls(pow26[i], pow26[i - 1], 26);
		iadd(pow26_sums[i], pow26_sums[i - 1], pow26[i]);
	}

	for (;;) {
		for (i = 0; (c = getchar()) != EOF && c != '\n';)
			if ((c >= '0' && c <= '9') ||
			    (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
				buf[i++] = c;
		buf[i] = '\0';

		if (c == EOF)
			break;

		if (i == 0)
			continue;

		if (buf[0] >= '0' && buf[0] <= '9')
			giveword(buf);
		else
			givenum(buf, i);
	}

	return 0;
}
