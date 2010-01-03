#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bitset(p,n) p[(n) >> 3] |= 1 << ((n) & 7)
#define bitclr(p,n) p[(n) >> 3] &= ~(1 << ((n) & 7))
#define bitget(p,n) ((p[(n) >> 3] >> ((n) & 7)) & 1)

#define ARRSIZE	2330000
#define LASTNUM 18409500
typedef unsigned char byte;

static int twins[100100];

int main(void)
{
	register int i;
	register byte *a;
	int t, n;

	a = (byte *)malloc(ARRSIZE);
	memset(a, 0x55, ARRSIZE);

	for (i = 3; i < LASTNUM; i += 2) {
		if (bitget(a, i) == 0) {
			register int j;
			for (j = i + i; j < LASTNUM; j += i)
				bitset(a, j);
		}
	}

	t = 1; twins[t++] = 4;
	for (i = 6; i < LASTNUM; i += 6)
		if (bitget(a, i - 1) == 0 && bitget(a, i + 1) == 0) {
			twins[t++] = i;
			if (t > 100010) break;
		}
	free(a);

	while (scanf("%d", &n) > 0)
		printf("(%d, %d)\n", twins[n]-1, twins[n]+1);

	return 0;
}
