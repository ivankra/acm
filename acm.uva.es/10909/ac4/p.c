#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 333700

static int left[MAXN], right[MAXN], parent[MAXN], key[MAXN], count[MAXN], last, root;
static unsigned map[65536];

#define IS(x) ((map[(x) >> 5] >> ((x) & 31)) & 1)

static int sol(int n)
{
	int a;

	if (n <= 1 || (n & 1) == 1)
		return -1;

	a = (n >> 1);
	while (a > 0 && !IS(a)) a--;

	for (; a > 0; a -= 2)
		if (IS(a) && IS(n - a)) return a;

	return -1;
}

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

static void rem(int k)
{
	int x, y;

	for (x = root;;) {
		count[x]--;
		if (k < count[left[x]])
			x = left[x];
		else if (k == count[left[x]])
			break;
		else
			k -= count[left[x]] + 1, x = right[x];
	}

	if (left[x] != 0 && right[x] != 0) {
		if (count[right[x]] >= count[left[x]])
			for (y = right[x]; left[y] != 0; y = left[y])
				count[y]--;
		else
			for (y = left[x]; right[y] != 0; y = right[y])
				count[y]--;
		key[x] = key[y];
		x = y;
	}

	if (left[x] == 0 && right[x] == 0) {
		if (left[parent[x]] == x)
			left[parent[x]] = 0;
		else
			right[parent[x]] = 0;
		return;
	}

	y = (left[x] == 0) ? right[x] : left[x];

	if (parent[x] == 0) {
		parent[root = y] = 0;
		return;
	}

	if (left[parent[x]] == x)
		left[parent[x]] = y;
	else
		right[parent[x]] = y;
	parent[y] = parent[x];
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
	parent[left[t]] = parent[right[t]] = t;
	return t;
}

static void rec(int x)
{
	for (; x; x = right[x])
		map[key[x] >> 5] |= 1 << (key[x] & 31), rec(left[x]);
}

static void make()
{
	int i, j, k;

	last = 0;
	count[0] = 0;
	root = build(0, 333680);
	parent[root] = 0;

	for (i = 1, j = 1; i <= 333690; j += 6) {
		key[i++] = j;
		key[i++] = j + 2;
	}

	for (k = 2;; k++) {
		j = find(k) - 1;
		if (j >= count[root]) break;

		for (i = j; i < count[root]; i += j)
			rem(i);
	}
	rec(root);
}

int read(int, char *, int);
int write(int, char *, int);

int main()
{
	static char inbuf[1048576], outbuf[8*1048576], tmp[256];
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
