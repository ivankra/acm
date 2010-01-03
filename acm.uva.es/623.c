#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RADIX		1000000000
#define DIG_PER_LIMB	9
#define NR_LIMBS	288

typedef unsigned long limb_t;
typedef unsigned long long xlimb_t;

void mul1(limb_t x[], int k)
{
	register int i;
	register xlimb_t c;

	for (i = 0, c = 0; i < NR_LIMBS; i++) {
		c += (xlimb_t)k * (xlimb_t)x[i];
		if (c == 0) {
			x[i] = 0;
		} else {
			x[i] = c % RADIX;
			c /= RADIX;
		}
	}

}

char *print(limb_t x[])
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

	return strdup(p);
}

#define MAXFACT 1002

int main()
{
	static char *fact[MAXFACT];
	int i, n;
	static limb_t x[NR_LIMBS];

	for (i = 0; i < NR_LIMBS; i++)
		x[i] = i ? 0 : 1;

	fact[0] = fact[1] = "1";
	for (i = 2; i < MAXFACT; i++) {
		mul1(x, i);
		fact[i] = print(x);
	}

	while (scanf("%d", &n) > 0)
		printf("%d!\n%s\n", n, fact[n]);

	return 0;
}
