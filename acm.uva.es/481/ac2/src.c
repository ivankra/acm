#include <stdio.h>
#include <stdlib.h>

int read(int, char *, int);
int write(int, char *, int);

int x[131072], y[131072], z[131072], n, k;
char inbuf[2048576], outbuf[2048576], *xp[131072];

static void take()
{
	static int d[256], z[256];
	char *p;
	int i, j;

	for (i = 0; i < 256; i++) d[i] = 0;
	for (i = '0'; i <= '9'; i++) d[i] = 1;

	for (i = 0; i < 256; i++) z[i] = 1;
	for (i = '0'; i <= '9'; i++) z[i] = 0;
	z[0] = 0; z['-'] = 0;

	i = read(0, p = inbuf, sizeof(inbuf) - 1);
	inbuf[i] = '\0';
	inbuf[i + 1] = '\0';

	for (i = 0;;) {
		while (z[*p]) p++;
		xp[i] = p;
		if (*p == '-') {
			p++;
			for (j = *p++ - '0'; d[*p];) j = j * 10 + *p++ - '0';
			*p++ = '\0';
			x[i++] = -j;
		} else if (*p == '\0') {
			break;
		} else {
			for (j = *p++ - '0'; d[*p];) j = j * 10 + *p++ - '0';
			*p++ = '\0';
			x[i++] = j;
		}
	}

	n = i;
}

static void solve()
{
	int i, j, a, b;

	k = 1;
	z[1] = x[0];
	y[0] = 1;

	for (i = 1; i < n; i++) {
		if (x[i] > z[k]) {
			y[i] = ++k;
			z[k] = x[i];
			continue;
		}

		for (a = 1, b = k; (b - a) > 1;)
			if (z[j = (a + b) >> 1] < x[i])
				a = j + 1;
			else
				b = j;
		if (z[a] < x[i]) a++;

		y[i] = a;
		if (x[i] < z[a]) z[a] = x[i];
	}

	for (a = k, i = n - 1; y[i] != k; i--);

	for (b = x[z[--a] = i]; i >= 0; i--)
		if (y[i] == a && x[i] < b) b = x[z[--a] = i];
}

static void print()
{
	char *p, *q;
	int i;

	sprintf(p = outbuf, "%d\n-\n", k);
	while (*p) p++;

	for (i = 0; i < k; i++) {
		for (q = xp[z[i]]; *q;) *p++ = *q++;
		*p++ = '\n';
	}

	write(1, outbuf, p - outbuf);
}

void main2()
{
	take();
	solve();
	print();
	exit(0);
}
