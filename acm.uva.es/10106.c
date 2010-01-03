#include <stdio.h>
#include <stdlib.h>

#define RADIX		1000000000
#define DIG_PER_LIMB	9
#define NR_LIMBS	64

typedef unsigned long limb_t;
typedef unsigned long long xlimb_t;

void mul(limb_t z[], const limb_t x[], const limb_t y[])
{
	register int i, j;
	register xlimb_t c, k;
	int m;

	for (i = 0; i < NR_LIMBS; i++)
		z[i] = 0;

	for (i = 0; ; i++)
		if (i >= NR_LIMBS)
			return;
		else if (x[i] != 0 || y[i] != 0)
			break;

	for (m = 0; m < NR_LIMBS; m++) {
		k = (xlimb_t)y[m];
		if (k == 0)
			continue;

		for (i = 0, j = m, c = 0; j < NR_LIMBS; i++, j++) {
			c += k * (xlimb_t)x[i] + (xlimb_t)z[j];
			if (c == 0) {
				z[j] = 0;
			} else {
				z[j] = c % RADIX;
				c /= RADIX;
			}
		}
	}
}

int read(limb_t x[])
{
	static char buf[NR_LIMBS * DIG_PER_LIMB];
	int i, j, c;
	limb_t t;

	for (i = 0; i < (NR_LIMBS * DIG_PER_LIMB);) {
		if ((c = getchar()) == EOF) break;

		if (c >= '0' && c <= '9')
			buf[i++] = (c - '0');
		else if (i != 0)
			break;
	}

	if (i == 0)
		return 0;

	for (j = (NR_LIMBS * DIG_PER_LIMB) - 1, i--; i >= 0;)
		buf[j--] = buf[i--];

	while (j >= 0)
		buf[j--] = 0;

	for (i = NR_LIMBS - 1, c = 0; i >= 0; i--) {
		for (j = 0, t = 0; j < DIG_PER_LIMB; j++)
			t = t * 10 + buf[c++];
		x[i] = t;
	}

	return 1;
}

void print(limb_t x[])
{
	static char buf[(NR_LIMBS * DIG_PER_LIMB) + 16];
	char *p;
	int i, j;

	p = buf + (NR_LIMBS * DIG_PER_LIMB);
	*p-- = '\0';

	for (i = 0; i < NR_LIMBS; i++) {
		register limb_t t;

		for (t = x[i], j = 0; t != 0 && j < DIG_PER_LIMB; j++) {
			*p-- = '0' + (t % 10);
			t /= 10;
		}

		while (j++ < DIG_PER_LIMB)
			*p-- = '0';
	}

	for (p = buf; *p == '0'; p++);

	if (*p == '\0')
		printf("0\n");
	else
		printf("%s\n", p);
}

int main()
{
	static limb_t x[NR_LIMBS], y[NR_LIMBS], z[NR_LIMBS];

	while (read(x) > 0 && read(y) > 0) {
		mul(z, x, y);
		print(z);
	}

	return 0;
}
