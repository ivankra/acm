/*
ID: mjf28791
PROG: buylow
LANG: C
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NLIMBS 128

typedef struct {
	unsigned a[NLIMBS];
} num_t;

int seq_a[8192], seq_d[8192], got[8192], val[8192], nval, len;
num_t seq_m[8192];

void set(num_t *z, unsigned x)
{
	int i;
	for (z->a[0] = x, i = 1; i < NLIMBS; i++)
		z->a[i] = 0;
}

void add(num_t *z, num_t *x)
{
	unsigned i, c;

	for (c = 0, i = 0; i < NLIMBS; i++, c >>= 16)
		z->a[i] = (c += z->a[i] + x->a[i]) & 0xFFFF;
}

int iszero(num_t *z)
{
	int i;

	for (i = 0; i < NLIMBS; i++)
		if (z->a[i] != 0) return 0;

	return 1;
}

unsigned div1(num_t *z, unsigned d)
{
	unsigned r;
	int i;

	for (r = 0, i = NLIMBS - 1; i >= 0; i--) {
		r = (r << 16) | z->a[i];
		z->a[i] = r / d;
		r %= d;
	}

	return r;
}

char *fmt(num_t *x)
{
	static char s[1024], t[1024];
	int i, j;

	for (i = 0; i == 0 || !iszero(x);)
		s[i++] = div1(x, 10) + '0';

	for (j = 0; i-- > 0;)
		t[j++] = s[i];
	t[j] = '\0';

	return t;
}

int cmp(const void *p, const void *q)
{
	return *(int *)p - *(int *)q;
}

int find(int x)
{
	int a, b, c;

	for (a = 0, b = nval - 1;;) {
		if (val[c = (a + b) >> 1] < x)
			a = c + 1;
		else if (val[c] > x)
			b = c - 1;
		else
			return c;
	}
}

int main()
{
	int i, j;

	freopen("buylow.in", "r", stdin);
	freopen("buylow.out", "w", stdout);

	scanf("%d", &len);
	for (i = 0; i < len; i++)
		scanf("%d", &seq_a[i]);
	seq_a[len] = -1;

	for (i = 0; i <= len; i++)
		val[i] = seq_a[i];

	qsort(val, len+1, sizeof(val[0]), &cmp);

	for (nval = 0, i = 0; i <= len; i++)
		if (i == 0 || val[i - 1] != val[i]) val[nval++] = val[i];

	for (i = 0; i <= len; i++)
		seq_a[i] = find(seq_a[i]);

	for (i = 0; i < nval; i++)
		got[i] = -1;

	seq_d[0] = 1;
	set(&seq_m[0], 1);

	for (i = 1; i <= len; i++) {
		seq_d[i] = 1;
		for (j = i - 1; j >= 0; j--)
			if (seq_a[j] > seq_a[i] && (seq_d[j] + 1) > seq_d[i])
				seq_d[i] = seq_d[j] + 1;

		if (seq_d[i] == 1) {
			set(&seq_m[i], 1);
			continue;
		}

		set(&seq_m[i], 0);
		for (j = i - 1; j >= 0; j--) {
			if (seq_a[j] > seq_a[i] && (seq_d[j] + 1) == seq_d[i] &&
			    got[seq_a[j]] != i) {
				add(&seq_m[i], &seq_m[j]);
				got[seq_a[j]] = i;
			}
		}
	}

	printf("%d %s\n", seq_d[len] - 1, fmt(&seq_m[len]));

	return 0;
}
