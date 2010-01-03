#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 262144

typedef struct {
	int x, y;
} pt_t;

int left[MAXN], right[MAXN], parent[MAXN], key[MAXN], count[MAXN], total, root;
int height[MAXN], n;
pt_t pt[MAXN];
int score1[MAXN], score2[MAXN];
int line_s[MAXN], line_o[MAXN];

int cmpx(const void *p, const void *q)
{
	pt_t *a = (pt_t *)p, *b = (pt_t *)q;
	return (a->x != b->x) ? (a->x - b->x) : (a->y - b->y);
}

int cmpi(const void *p, const void *q)
{
	return *(int *)p - *(int *)q;
}

void ptree(int x)
{
	if (x == 0)
		printf(".");
	else {
		printf("(");
		ptree(left[x]);
		printf((count[x] == 1) ? " %d " : " %d:%d ", key[x], count[x]);
		ptree(right[x]);
		printf(")");
	}
}

void print(int r)
{
	ptree(r);
	printf("\n");
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int rotl(int x)
{
	int a, b, c, y, t;

	y = right[x];
	a = left[x];
	b = left[y];
	c = right[y];

	right[x] = b;
	parent[b] = x;

	t = parent[x];
	if (t == 0)
		root = y;
	else if (left[t] == x)
		left[t] = y;
	else
		right[t] = y;
	parent[y] = t;

	left[y] = x;
	parent[x] = y;

	t = count[x];
	count[x] = count[x] - count[y] + count[b];
	count[y] = t;

	height[x] = max(height[a], height[b]) + 1;
	height[y] = max(height[x], height[c]) + 1;

	return y;
}

int rotr(int y)
{
	int a, b, c, x, t;

	x = left[y];
	a = left[x];
	b = right[x];
	c = right[y];

	left[y] = b;
	parent[b] = y;

	t = parent[y];
	if (t == 0)
		root = x;
	else if (left[t] == y)
		left[t] = x;
	else
		right[t] = x;
	parent[x] = t;

	right[x] = y;
	parent[y] = x;

	t = count[y];
	count[y] = count[y] - count[x] + count[b];
	count[x] = t;

	height[y] = max(height[b], height[c]) + 1;
	height[x] = max(height[a], height[y]) + 1;

	return x;
}

void insert(int k)
{
	int x;

	if (root == 0) {
		left[0] = right[0] = parent[0] = height[0] = key[0] = count[0] = 0;
		left[1] = right[1] = parent[1] = 0;
		count[1] = height[1] = total = root = 1;
		key[1] = k;
		return;
	}

	for (total++, x = root;;) {
		if (k < key[x]) {
			if (left[x] == 0) {
				left[x] = total;
				break;
			}
			x = left[x];
		} else if (k > key[x]) {
			if (right[x] == 0) {
				right[x] = total;
				break;
			}
			x = right[x];
		} else {
			for (; x != 0; x = parent[x])
				count[x]++;
			return;
		}
	}

	parent[total] = x;
	x = total;
	key[x] = k;
	left[x] = 0;
	right[x] = 0;
	count[x] = 1;
	height[x] = 1;

	for (x = parent[x]; x != 0; x = parent[x]) {
		count[x]++;
		height[x] = max(height[left[x]], height[right[x]]) + 1;

		if (height[left[x]] < (height[right[x]] - 1))
			x = rotl(x);
		else if (height[right[x]] < (height[left[x]] - 1))
			x = rotr(x);
	}
}

int find_less(int k)
{
	int r, x;

	for (r = 0, x = root; x != 0;) {
		if (k < key[x]) {
			x = left[x];
		} else if (k > key[x]) {
			r += count[x] - count[right[x]];
			x = right[x];
		} else {
			r += count[left[x]];
			break;
		}
	}

	return r;
}

int find_greater(int k)
{
	int r, x;

	for (r = 0, x = root; x != 0;) {
		if (k < key[x]) {
			r += count[x] - count[left[x]];
			x = left[x];
		} else if (k > key[x]) {
			x = right[x];
		} else {
			r += count[right[x]];
			break;
		}
	}

	return r;
}

int main()
{
	int i, j, k, s;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &pt[i].x, &pt[i].y);
		qsort(pt, n, sizeof(pt[0]), &cmpx);

		memset(score1, 0, n * sizeof(int));
		memset(score2, 0, n * sizeof(int));

		for (root = 0, i = 0; i < n; i = j) {
			for (j = i; j < n && pt[j].x == pt[i].x; j++) {
				score1[j] += find_less(pt[j].y);
				score2[j] += find_greater(pt[j].y);
			}

			for (j = i; pt[j].x == pt[i].x; j++)
				insert(pt[j].y);
		}

		for (root = 0, i = n - 1; i >= 0; i = j) {
			for (j = i; j >= 0 && pt[j].x == pt[i].x; j--) {
				score2[j] += find_less(pt[j].y);
				score1[j] += find_greater(pt[j].y);
			}

			for (j = i; j >= 0 && pt[j].x == pt[i].x; j--)
				insert(pt[j].y);
		}

		for (k = 0, i = 0; i < n; i = j, k++) {
			line_s[k] = score1[i];
			line_o[k] = score2[i];
			for (j = i; j < n && pt[j].x == pt[i].x; j++) {
				if (score1[j] < line_s[k]) line_s[k] = score1[j];
				if (score2[j] > line_o[k]) line_o[k] = score2[j];
			}
		}

		for (s = line_s[0], i = 0; i < k; i++)
			if (line_s[i] > s) s = line_s[i];

		for (j = 0, i = 0; i < k; i++)
			if (line_s[i] == s) key[j++] = line_o[i];

		qsort(key, j, sizeof(key[0]), &cmpi);

		printf("Stan: %d; Ollie:", s);
		for (i = 0; i < j; i++)
			if (i == 0 || key[i - 1] != key[i])
				printf(" %d", key[i]);
		printf(";\n");
	}

	return 0;
}
