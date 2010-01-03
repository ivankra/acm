#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 254500

static int left[MAXN], right[MAXN], key[MAXN], count[MAXN], last, root;
static unsigned map[65536];

#define IS(x) ((map[(x) >> 5] >> ((x) & 31)) & 1)

/* Finds position of k-th smallest element */
static int find(int k)
{
	int x;

	for (x = root;;) {
		if (k < count[left[x]])
			x = left[x];
		else if (k == count[left[x]])
			return key[x];
		else
			k -= count[left[x]] + 1, x = right[x];
	}
}

/* Removes k-th smallest element */
static void rem(int k)
{
	int x, y, z;

	for (x = root, z = 0;;) {
		count[x]--;
		if (k == count[left[x]])
			break;
		z = x;
		if (k < count[left[x]])
			x = left[x];
		else
			k -= count[left[x]] + 1, x = right[x];
	}

	if (left[x] != 0 && right[x] != 0) {
		if (count[right[x]] >= count[left[x]])
			for (y = right[z = x]; left[y] != 0;) {
				count[y]--;
				z = y;
				y = left[y];
			}
		else
			for (y = left[z = x]; right[y] != 0;) {
				count[y]--;
				z = y;
				y = right[y];
			}
		key[x] = key[y];
		x = y;
	}

	if (left[x] == 0 && right[x] == 0) {
		if (left[z] == x)
			left[z] = 0;
		else
			right[z] = 0;
		return;
	}

	y = (left[x] == 0) ? right[x] : left[x];

	if (z == 0) {
		root = y;
			return;
	}

	if (left[z] == x)
		left[z] = y;
	else
		right[z] = y;
}

static int build(int a, int b)
{
	int c, t;

	if (a == b) {
		count[++last] = 1;
		return last;
	}

	c = (a + b) >> 1;
	if (a < c) t = build(a, c - 1); else t = 0;

	left[++last] = t;
	t = last;
	if (++c <= b) right[t] = build(c, b);
	count[t] = count[left[t]] + count[right[t]] + 1;
	return t;
}

static void rec(int x)
{
	for (; x; x = right[x])
		map[key[x] >> 5] |= 1 << (key[x] & 31), rec(left[x]);
}

static void make()
{
	/*  [sieved out: 2,3,7,9; no: 254234;
	    252n+ */
	static int p[] = {
		1, 3, 7, 9, 13, 15, 21, 25, 31, 33, 37, 43, 45, 49, 51, 55,
		63, 67, 69, 73, 75, 79, 85, 87, 93, 97, 99, 105, 109, 111,
		115, 117, 127, 129, 133, 135, 139, 141, 147, 151, 157, 159,
		163, 169, 171, 175, 177, 181, 189, 193, 195, 199, 201, 205,
		211, 213, 219, 223, 225, 231, 235, 237, 241, 243
	};
	int i, j, k;

	last = 0;
	count[0] = 0;
	root = build(0, 254234);
	for (i = 1, j = 0; i <= 254260; j += 252)
		for (k = 0; k < 64; k++)
			key[i++] = j + p[k];

	for (k = 4;; k++) {
		j = find(k) - 1;
		if (j >= count[root]) break;

		for (i = j; i < count[root]; i += j)
			rem(i);
	}
	rec(root);
}

static int sol(int n)
{
	int a;

	if (n <= 1 || (n & 1) == 1)
		return -1;

	a = (n >> 1);
	while (a > 0 && !IS(a)) a--;

	for (;; a -= 2)
		if (IS(a) && IS(n - a)) return a;
}

int read(int, char *, int);
int write(int, char *, int);

int main()
{
	static char inbuf[1048576], outbuf[4*1048576], tmp[256];
	static int isdig[256], isdigx[256];
	char *p, *q, *s;
	int i, n;

	for (i = '0'; i <= '9'; i++) isdig[i] = isdigx[i] = 1; isdigx[0] = 1;
	inbuf[read(0, p = inbuf, sizeof(inbuf))] = 0;
	q = outbuf;

	make();

	for (;;) {
		while (!isdigx[*p]) p++;
		if (*p == '\0') break;

		for (n = *p++ - '0'; isdig[*p];)
			n = n * 10 + *p++ - '0';

		i = sol(n);

#define W(ex) {int x=(ex);for(s=tmp;x>0;x/=10)*s++=(x%10)+'0';while(s-->tmp)*q++=*s;}

		W(n);

		if (i < 0) {
			for (s = " is not the sum of two luckies!\n"; *s;) *q++ = *s++;
		} else {
			for (s = " is the sum of "; *s;) *q++ = *s++;
			W(i);
			*q++ = ' '; *q++ = 'a'; *q++ = 'n'; *q++ = 'd'; *q++ = ' ';
			W(n - i);
			*q++ = '.'; *q++ = '\n';
		}
	}

	write(1, outbuf, q - outbuf);
	exit(0);
}
