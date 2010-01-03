#include <stdio.h>
#include <string.h>

#define NLIMBS 24

typedef unsigned long u_int32_t;
typedef u_int32_t num_t[NLIMBS];

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

void print(num_t x)
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

	printf("%s\n", buf2);
}

int main()
{
	static num_t buf1[256], buf2[256], s;
	static int b, n;
	register int i, k;
	register num_t *tab, *tabnext;

	while (scanf("%d %d", &b, &n) == 2 && b > 0) {
		tab = buf1;
		tabnext = buf2;

		for (set(tab[0], 0), i = 1; i < b; i++)
			set(tab[i], 1);

		for (k = 1; k <= n;) {
			for (set(s, 0), i = 0; i < b; i++)
				add(s, tab[i]);

			if (k++ == n)
				break;

			for (i = 0; i < b; i++)
				memcpy(tabnext[i], s, sizeof(num_t));
			sub(tabnext[3], tab[1]);

			tab = tabnext;
			tabnext = (tabnext == buf1) ? buf2 : buf1;
		}

		print(s);
	}

	return 0;
}
