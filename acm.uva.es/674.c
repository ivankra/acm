#include <stdio.h>

#define MAXC 7491

static unsigned a[MAXC];

static void make(void)
{
	register int i, j;

	for (i = 0; i < MAXC; i++) a[i] = 1;
	for (i = 5, j = 0; i < MAXC;) a[i++] += a[j++];
	for (i = 10, j = 0; i < MAXC;) a[i++] += a[j++];
	for (i = 25, j = 0; i < MAXC;) a[i++] += a[j++];
	for (i = 50, j = 0; i < MAXC;) a[i++] += a[j++];
}

int main()
{
	static int n;

	make();
	while (scanf("%d", &n) == 1)
		printf("%u\n", a[n]);

	return 0;
}
