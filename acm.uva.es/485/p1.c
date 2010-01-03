#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define NROWS	205

#if 0
typedef unsigned long limb_t;
#define NLIMBS		8
#define RADIX		1000000000
#define RADIX_L10	9
#else
typedef unsigned long long limb_t;		/* 2^64 = 10^19.2659... */
#define NLIMBS		4
#define RADIX		1000000000000000000
#define RADIX_L10	18
#endif

void prn(limb_t *x)
{
	register limb_t t;
	register int i, j, f;
	static char buf[RADIX_L10];

	for (i = NLIMBS - 1, f = 0; i >= 0; i--) {
		t = x[i];
		if (f == 0 && t == 0)
			continue;

		for (j = 0; t != 0; t /= 10)
			buf[j++] = t % 10;
		if (f == 0) {
			f = 1;
		} else {
			while (j < RADIX_L10)
				buf[j++] = 0;
		}

		while (j-- > 0)
			putchar('0' + buf[j]);
	}

	if (f == 0)
		putchar('0');
}

static limb_t limb_buf1[NROWS * NLIMBS];
static limb_t limb_buf2[NROWS * NLIMBS];

int main(void)
{
	limb_t *x, *y;
	int n;
	register int i;

	memset((void *)limb_buf1, 0, sizeof(limb_buf1));
	memset((void *)limb_buf2, 0, sizeof(limb_buf2));
	x = limb_buf1;
	y = limb_buf2;
	x[0] = 1;
	y[0] = 1;

	for (n = 1; n <= NROWS; n++) {
		for (i = 0; i < n; i++) {
			if (i != 0) putchar(' ');
			prn(x + (i * NLIMBS));
		}
		putchar('\n');

		for (i = 1; i <= n; i++) {
			register int j, c, k;
			for (j = 0, c = 0; j < NLIMBS; j++) {
				k = i * NLIMBS + j;
				y[k] = x[k] + x[k - NLIMBS];
				if (c != 0)
					y[k]++;
				if (y[k] >= RADIX) {
					y[k] -= RADIX;
					c = 1;
				} else {
					c = 0;
				}
			}
		}

		{ register limb_t *p = x; x = y; y = p; }
	}

}
