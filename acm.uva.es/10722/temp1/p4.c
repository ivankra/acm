#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NLIMBS 24

typedef unsigned long u_int32_t;
typedef u_int32_t num_t[NLIMBS];

static num_t result[130][128];
static char *result_s[130][128];

void set(num_t x, u_int32_t y)
{
	int i;

	for (x[0] = y, i = 1; i < NLIMBS; i++)
		x[i] = 0;
}

void add(num_t x, num_t y)
{
	int i;
	u_int32_t c;

	for (i = 0, c = 0; i < NLIMBS; i++, c >>= 31) {
		c += x[i] + y[i];
		x[i] = c & 0x7FFFFFFF;
	}
}

void sub(num_t x, num_t y)
{
	int i;
	u_int32_t c;

	for (i = 0, c = 1; i < NLIMBS; i++, c >>= 31) {
		c += x[i] + (y[i] ^ 0x7FFFFFFF);
		x[i] = c & 0x7FFFFFFF;
	}
}

char *format(num_t x)
{
	static char buf[1024], buf2[1024];
	unsigned long long r;
	int i, k;
	char *s;

	for (s = buf;;) {
		for (i = NLIMBS - 1, r = 0; i >= 0; i--) {
			r = (r << 31) | (unsigned long long)x[i];
			x[i] = (u_int32_t)(r / 1000000000ULL);
			r %= 1000000000ULL;
		}

		for (k = 0, i = r; k < 9; k++, i /= 10)
			*s++ = (i % 10) + '0';

		for (i = 0; i < NLIMBS; i++)
			if (x[i]) break;

		if (i >= NLIMBS)
			break;
	}

	for (s--; s > buf && *s == '0'; s--);

	for (i = 0; s >= buf;)
		buf2[i++] = *s--;
	buf2[i] = '\0';

	s = (char *)malloc(i + 1);
	strcpy(s, buf2);

	return s;
}

static void compute(int b)
{
	static num_t buf1[256], buf2[256], s;
	register int i, k;
	register num_t *tab, *tabnext;

	tab = buf1;
	tabnext = buf2;

	for (set(tab[0], 0), i = 1; i < b; i++)
		set(tab[i], 1);

	for (k = 1;;) {
		for (set(s, 0), i = 0; i < b; i++)
			add(s, tab[i]);

		memcpy(result[b][k], s, sizeof(num_t));

		if (++k > 100)
			break;

		for (i = 0; i < b; i++)
			memcpy(tabnext[i], s, sizeof(num_t));
		sub(tabnext[3], tab[1]);

		tab = tabnext;
		tabnext = (tabnext == buf1) ? buf2 : buf1;
	}
}

int main()
{
	static int computed[128];
	int b, n;

	memset(computed, 0, sizeof(computed));
	memset(result_s, 0, sizeof(result_s));

	while (scanf("%d %d", &b, &n) == 2 && b > 0) {
		if (!computed[b])
			compute(b);

		if (result_s[b][n] == NULL)
			result_s[b][n] = format(result[b][n]);

		printf("%s\n", result_s[b][n]);
	}

	return 0;
}
