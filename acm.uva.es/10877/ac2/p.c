#include <stdio.h>
#include <string.h>

int read(int, char *, int);

static char inbuf[1048576], *inp;
static int isdig[256];

#define READ(x) \
	{ while (!isdig[(int)*inp]) inp++; \
	  for (x = *inp++ - '0'; isdig[(int)*inp];) x = x * 10 + *inp++ - '0'; }

static void xrot(int a[])
{
	int t = a[0];
	a[0] = a[1];
	a[1] = a[3];
	a[3] = a[5];
	a[5] = t;
}

static void yrot(int a[])
{
	int t = a[0];
	a[0] = a[4];
	a[4] = a[3];
	a[3] = a[2];
	a[2] = t;
}

static void zrot(int a[])
{
	int t = a[1];
	a[1] = a[2];
	a[2] = a[5];
	a[5] = a[4];
	a[4] = t;
}

static int get()
{
	static int a[6];
	int i, r, t, x, y, z;

	for (i = 0; i < 6; i++) {
		READ(t);
		a[i] = t - 1;
	}

	for (r = 0x3FFFFFFF, x = 0; x < 4; x++, xrot(a)) {
		for (y = 0; y < 4; y++, yrot(a)) {
			for (z = 0; z < 4; z++, zrot(a)) {
				for (t = 0, i = 0; i < 6; i++)
					t = t * 6 + a[i];
				if (t < r) r = t;
			}
		}
	}

	return r;
}

static void sort(int a[], int n)
{
	int i, j, p, t;

re:	if (n <= 32) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	for (p = a[(n - 1) >> 1], i = -1, j = n;;) {
		while (a[++i] < p);
		while (a[--j] > p);

		if (i >= j)
			break;

		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	if ((n - i) > 1)
		sort(a + i, n - i);

	n = i;
	goto re;
}

int main()
{
	static int a[65536];
	int i, r, n;

	for (i = 0; i < 256; i++)
		isdig[i] = ('0' <= i && i <= '9');

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

	for (;;) {
		READ(n);
		if (n == 0) break;

		for (i = 0; i < n; i++)
			a[i] = get();

		sort(a, n);

		for (r = 1, i = 1; i < n; i++)
			if (a[i - 1] != a[i]) r++;
		printf("%d\n", r);
	}

	return 0;
}
