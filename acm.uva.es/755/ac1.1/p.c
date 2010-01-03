#include <stdio.h>

#define MAXN 100010

/* Sorts an array of n integers in ascending order */
static void sort(int a[], int n)
{
	int i, j, p, t;

re:
	if (n <= 32) {
		/* Insertion sort */
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}

		return;
	}

	/* Quicksort algorithm */

	/* Hoare's partitioning algorithm */
	for (p = a[(n - 1) >> 1], i = -1, j = n;;) {
		while (a[++i] < p);
		while (a[--j] > p);

		if (i >= j)
			break;

		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	/* Now: a[0..i-1] <= p, a[i..n] >= p */

	/* Sort the second part recursively */
	if ((n - i) > 1)
		sort(a + i, n - i);

	/* Sort the first part */
	n = i;
	goto re;	/* `goto' instead of tail recursion */
}

/*
 *  dig[]: conversion table from each character code to corresponding digit.
 *  valid[]: boolean table, valid[i] != 0 indicates that character code `i' is
 *    a valid phone number's digit.
 */
static int dig[256], valid[256];

/* Prepares tables dig[] and valid[]; based on problem's description */
static void maketabs()
{
	char *p, *tab[10] = {
		"0", "1", "2ABCabc", "3DEFdef", "4GHIghi", "5JKLjkl",
		"6MNOmno", "7PRSprs", "8TUVtuv", "9WXYwxy"
	};
	int i;

	for (i = 0; i < 256; i++)
		dig[i] = valid[i] = 0;

	for (i = 0; i < 10; i++) {
		for (p = tab[i]; *p; p++) {
			dig[*p] = i;
			valid[*p] = 1;
		}
	}
}

int main()
{
	static int a[MAXN], n, t, x, dupes;
	static char buf[1024];
	register int i, k;
	register char *p;

	maketabs();

	scanf("%d\n\n", &t);

	while (t-- > 0 && scanf("%d\n", &n) == 1) {
		/* Parse input, convert phones to integers, and put them to a[] */
		for (i = 0; i < n && fgets(buf, sizeof(buf), stdin); i++) {
			for (p = buf, k = 0; *p; p++)
				if (valid[*p])
					k = k * 10 + dig[*p];
			a[i] = k;
		}

		/* Sort the array, so that equal numbers are grouped together */
		sort(a, n);

		/* Scan through the array, find and report duplicates */
		for (i = 0, dupes = 0; i < n; ) {
			for (x = a[i++], k = 1; i < n && a[i] == x; i++, k++);

			if (k == 1)
				continue;

			printf("%.3d-%.4d %d\n", x / 10000, x % 10000, k);
			dupes++;
		}

		if (dupes == 0)
			printf("No duplicates.\n");

		if (t > 0)
			printf("\n");
	}

	return 0;
}
