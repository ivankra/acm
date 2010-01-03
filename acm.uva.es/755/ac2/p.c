#include <stdio.h>

int read(int, char *, int);
int write(int, char *, int);

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

static int digits[256], valid[256];
static int array[131072], tleft, nphones;

static void show()
{
	static int dup;
	register int i, k, m;

	for (i = 0, dup = 0; i < nphones; ) {
		for (m = array[i++], k = 1; i < nphones && array[i] == m; i++, k++);

		if (k < 2)
			continue;

		printf("%.3d-%.4d %d\n", m / 10000, m % 10000, k);
		dup = 1;
	}

	if (!dup)
		printf("No duplicates.\n");

	if (tleft > 0)
		printf("\n");
}

static void maketabs()
{
	static char *tab[10] = {
		"0", "1", "2ABCabc", "3DEFdef", "4GHIghi", "5JKLjkl",
		"6MNOmno", "7PRSprs", "8TUVtuv", "9WXYwxy"
	};
	register int i;
	register char *p;

	for (i = 0; i < 256; i++)
		digits[i] = valid[i] = 0;

	for (i = 0; i < 10; i++) {
		for (p = tab[i]; *p; p++) {
			digits[(unsigned)*p] = i;
			valid[(unsigned)*p] = 1;
		}
	}
}

int main()
{
	static char inbuffer[65536];
	static int inleft, n, rflag;
	register char *inptr;

	maketabs();

	inleft = 0;
	inptr = inbuffer;

#define GET(var) \
	for (rflag = 0, var = 0;;) { \
		if (inleft == 0) { \
			inptr = inbuffer; \
			inleft = read(0, inbuffer, sizeof(inbuffer)); \
			if (inleft <= 0) { inleft = 0; break; } \
		} \
		if (valid[(unsigned)*inptr]) { \
			var = var * 10 + digits[(unsigned)*inptr++]; \
			inleft--; \
                        rflag = 1; \
		} else { \
			inleft--; \
			if (*inptr++ == '\n' && rflag) break; \
		} \
	}


	GET(tleft);

	while (tleft-- > 0) {
		GET(nphones);

		for (n = 0; n < nphones; n++)
			GET(array[n])

		sort(array, nphones);

		show();
	}

	return 0;
}
