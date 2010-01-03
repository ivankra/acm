#include <stdio.h>

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
	static int a[131072], dig[256], valid[256], n, t, x, dupes;
	static char buf[1024];
	register int i, k;
	register char *p;

	for (i = 0; i < 256; i++) dig[i] = 0;
	for (i = 0; i < 10; i++) dig[i + '0'] = i;
	for (p = "ABCDEFGHIJKLMNOPRSTUVWXY", i = 2; i <= 9; i++, p += 3)
		dig[p[0]] = dig[p[1]] = dig[p[2]] = i;
	for (p = "abcdefghijklmnoprstuvwxy", i = 2; i <= 9; i++, p += 3)
		dig[p[0]] = dig[p[1]] = dig[p[2]] = i;
	for (i = 0; i < 256; i++)
		valid[i] = ((i == '0') || (dig[i] != 0));

	scanf("%d\n\n", &t);
	while (t-- > 0 && scanf("%d\n", &n) == 1) {
		for (i = 0; i < n && fgets(buf, sizeof(buf), stdin); i++) {
			for (p = buf, k = 0; *p; p++)
				if (valid[*p]) k = k * 10 + dig[*p];
			a[i] = k;
		}

		sort(a, n);

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
