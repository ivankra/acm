#include <stdio.h>

int read(int, char *, int);

int sym[24][8] = {
	{ 0, 1, 2, 3, 4, 5 }, { 0, 2, 5, 3, 1, 4 }, { 0, 4, 1, 3, 5, 2 },
	{ 0, 5, 4, 3, 2, 1 }, { 1, 0, 4, 5, 2, 3 }, { 1, 2, 0, 5, 3, 4 },
	{ 1, 3, 2, 5, 4, 0 }, { 1, 4, 3, 5, 0, 2 }, { 2, 0, 1, 4, 5, 3 },
	{ 2, 1, 3, 4, 0, 5 }, { 2, 3, 5, 4, 1, 0 }, { 2, 5, 0, 4, 3, 1 },
	{ 3, 1, 4, 0, 2, 5 }, { 3, 2, 1, 0, 5, 4 }, { 3, 4, 5, 0, 1, 2 },
	{ 3, 5, 2, 0, 4, 1 }, { 4, 0, 5, 2, 1, 3 }, { 4, 1, 0, 2, 3, 5 },
	{ 4, 3, 1, 2, 5, 0 }, { 4, 5, 3, 2, 0, 1 }, { 5, 0, 2, 1, 4, 3 },
	{ 5, 2, 3, 1, 0, 4 }, { 5, 3, 4, 1, 2, 0 }, { 5, 4, 0, 1, 3, 2 }
};

int isdig[256];
char inbuf[1048576], *inp;

#define READ(x) \
	{ while (!isdig[(int)*inp]) inp++; \
	  for (x = *inp++ - '0'; isdig[(int)*inp];) x = x * 10 + *inp++ - '0'; }

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

void main2()
{
	static int a[1024], b[8];
	int i, j, k, r, t, n;

	/* memset(isdig, 0, sizeof(isdig)); */
	for (i = '0'; i <= '9'; i++)
		isdig[i] = 1;

	inbuf[read(0, inp = inbuf, sizeof(inbuf))] = '\0';

	for (;;) {
		READ(n);
		if (n == 0) break;

		for (i = 0; i < n; i++) {
			for (j = 0; j < 6; j++) {
				READ(k);
				b[j] = k - 1;
			}

			for (j = 0, r = 0x3FFFFFFF; j < 24; j++) {
				for (k = 0, t = 0; k < 6; k++)
					t = t * 6 + b[sym[j][k]];
				if (t < r) r = t;
			}

			a[i] = r;
		}

		sort(a, n);

		for (r = 1, i = 1; i < n; i++)
			if (a[i - 1] != a[i]) r++;
		printf("%d\n", r);
	}

	exit(0);
}

int main()
{
	main2();
	return 0;
}
