#include <stdio.h>
#include <string.h>

#define DIV  65521
#define MAXN 1048576

static int hash[DIV], freq[MAXN], value[MAXN], next[MAXN], last;
int read(int, char *, int);

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

static void wr(int x)
{
	static char s[8];
	int i, n;

	n = x >> 24;
	x &= 0xFFFFFF;

	for (i = 0; i < n; i++, x /= 26)
		s[i] = (x % 26) + 'A';

	while (i-- > 0)
		putchar(s[i]);
}

static void rep(int m)
{
	static int f[8], list[131072];
	int i, j, k;

	for (i = 0; i < 8; i++)
		f[i] = 0;

	for (i = 1; i <= last; i++) {
		if ((value[i] >> 24) != m)
			continue;

		if (freq[i] <= f[5] || freq[i] == f[1] || freq[i] == f[2] ||
		    freq[i] == f[3] || freq[i] == f[4] || freq[i] == f[5])
			continue;

		for (j = 4; j >= 1 && freq[i] > f[j]; j--)
			f[j + 1] = f[j];
		f[j + 1] = freq[i];
	}

	for (k = 1; k <= 5 && f[k] > 0; k++) {
		for (i = 1, j = 0; i <= last; i++)
			if ((value[i] >> 24) == m && freq[i] == f[k])
				list[j++] = value[i];
		sort(list, j);

		printf("Frequency = %d, Sequence(s) = (", f[k]);
		for (wr(list[0]), i = 1; i < j; i++) {
			putchar(',');
			wr(list[i]);
		}
		printf(")\n");
	}
}

static void add(int x)
{
	int i, r;

	for (i = hash[r = x % DIV]; i != 0; i = next[i]) {
		if (value[i] == x) {
			freq[i]++;
			return;
		}
	}

	value[++last] = x;
	freq[last] = 1;
	next[last] = hash[r];
	hash[r] = last;
}

int main()
{
	static char buffer[65537];
	static int alph[256], s[8];
	char *p;
	int i, c, k;

	memset(hash, 0, sizeof(hash));
	last = 0;

	for (i = 0; i < 256; i++)
		alph[i] = (i >= 'A' && i <= 'z') || (i >= 'a' && i <= 'z');

	for (*(p = buffer) = '\0', k = 0;;) {
		if (*p == '\0') {
			buffer[read(0, p = buffer, sizeof(buffer) - 1)] = '\0';
			if (buffer[0] == '\0')
				break;
		}

		if (alph[c = *p++] == 0) {
			k = 0;
			continue;
		}

		c = (c | 0x20) - 'a';

		s[5] = s[4] * 26 + c;
		s[4] = s[3] * 26 + c;
		s[3] = s[2] * 26 + c;
		s[2] = s[1] * 26 + c;
		s[1] = c;

		if (k < 5)
			k++;

		for (i = 1; i <= k; i++)
			add(s[i] | (i << 24));
	}

	for (c = 1; c <= 5; c++) {
		printf("Analysis for Letter Sequences of Length %d\n"
		       "-----------------------------------------\n", c);

		rep(c);

		/*if (c < 5)*/
			printf("\n");
	}

	return 0;
}
