#include <stdio.h>
#include <stdlib.h>

static int h[6000];

const char *suf[10] = {
	"th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th"
};

static void sort(int a[], int n)
{
	int j, i, v, t;

re:	if (n < 24) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	for (v = a[n >> 1], i = -1, j = n;;) {
		while (a[++i] < v);
		while (a[--j] > v);
		if (i >= j) break;
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
	int i, n, a, b, c, d;
	long long ha, hb, hc, hd;
		
	for (n = 0, ha = 1, a = 0; a < 31 && ha <= 2000000000; a++, ha *= 2)
		for (hb = ha, b = 0; b < 20 && hb <= 2000000000; b++, hb *= 3)
			for (hc = hb, c = 0; c < 14 && hc <= 2000000000; c++, hc *= 5)
				for (hd = hc, d = 0; d < 12 && hd <= 2000000000; d++, hd *= 7)
					h[n++] = (int)hd;

	sort(h, n);

	while (scanf("%d", &a) > 0 && a > 0) {
		printf("The %d%s humble number is %d.\n", a,
			((a % 100) <= 20 && (a % 100) >= 10) ? "th" : suf[a % 10],
			h[a - 1]);
	}

	return 0;
}
