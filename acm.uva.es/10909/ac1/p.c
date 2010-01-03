#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAXN 670000

int left[MAXN], right[MAXN], parent[MAXN], key[MAXN], count[MAXN], last, root;
unsigned map[65536];

#define IS(x) ((map[(x) >> 5] >> ((x) & 31)) & 1)

int sol(int n)
{
	int a;

	if (n <= 0 || n > 2000000 || (n & 1) == 1)
		return -1;

	a = (n >> 1);
	while (a > 0 && !IS(a)) a--;

	for (; a > 0; a -= 2)
		if (IS(a) && IS(n - a)) return a;

	return -1;
}

int find(int k)
{
	int x;

	for (x = root;;) {
		if (k < count[left[x]])
			x = left[x];
		else if (k == count[left[x]])
			return x;
		else
			k -= count[left[x]] + 1, x = right[x];
	}
}

void rem(int x)
{
	int y;

	if (left[x] != 0 && right[x] != 0) {
		if (count[right[x]] >= count[left[x]])
			for (y = right[x]; left[y] != 0; y = left[y]);
		else
			for (y = left[x]; right[y] != 0; y = right[y]);
		key[x] = key[y];
		x = y;
	}

	if (left[x] == 0 && right[x] == 0) {
		if (left[parent[x]] == x)
			left[parent[x]] = 0;
		else
			right[parent[x]] = 0;

		for (x = parent[x]; x != 0; x = parent[x])
			count[x]--;

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

	for (x = parent[x]; x != 0; x = parent[x])
		count[x]--;
}

int build(int a, int b)
{
	int c, t;

	if (a > b)
		return 0;

	if (a == b) {
		last++;
		left[last] = right[last] = 0;
		count[last] = 1;
		return last;
	}

	c = (a + b) >> 1;
	t = build(a, c - 1);

	last++;
	left[last] = t;
	t = last;
	right[t] = build(c + 1, b);
	count[t] = count[left[t]] + count[right[t]] + 1;
	parent[left[t]] = parent[right[t]] = t;
	return t;
}

void rec(int x)
{
	for (; x; x = right[x])
		map[key[x] >> 5] |= 1 << (key[x] & 31), rec(left[x]);
}

void make()
{
	int i, j, k;

	last = 0;
	count[0] = 0;
	root = build(0, 666667);
	parent[root] = 0;

	for (i = 1, j = 1; i <= 666700; j += 6) {
		key[i++] = j;
		key[i++] = j + 2;
	}

	for (k = 2; k < count[root]; k++) {
		j = key[find(k)] - 1;
		if (j >= count[root]) break;

		for (i = j; i < count[root]; i += j)
			rem(find(i));
	}

	memset(map, 0, sizeof(map));
	rec(root);
}

int main()
{
	int i, n;

	make();

	while (scanf("%d", &n) == 1) {
		i = sol(n);
		if (i < 0)
			printf("%d is not the sum of two luckies!\n", n);
		else
			printf("%d is the sum of %d and %d.\n", n, i, n - i);
	}

	return 0;
}
