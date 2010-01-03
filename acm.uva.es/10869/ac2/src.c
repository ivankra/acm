#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200001

int read(int, char *, int);

typedef struct {
	int x, y;
} pt_t;

int key[MAXN], count[MAXN], total;

static void xsort(pt_t a[], int n)
{
	int i, j, p;
	pt_t t;

re:	if (n < 12) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j].x > t.x; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	for (i = 0, j = n - 1, p = a[n >> 1].x;;) {
		while (a[i].x < p) i++;
		while (a[j].x > p) j--;

		if (i >= j)
			break;

		t = a[i];
		a[i++] = a[j];
		a[j--] = t;
	}

	if ((n - i) > 1)
		xsort(a + i, n - i);

	n = i;
	goto re;
}

static void ysort(pt_t a[], int n)
{
	int i, j, p;
	pt_t t;

re:	if (n < 12) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j].y > t.y; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	for (i = 0, j = n - 1, p = a[n >> 1].y;;) {
		while (a[i].y < p) i++;
		while (a[j].y > p) j--;

		if (i >= j)
			break;

		t = a[i];
		a[i++] = a[j];
		a[j--] = t;
	}

	if ((n - i) > 1)
		ysort(a + i, n - i);

	n = i;
	goto re;
}

static void isort(int a[], int n)
{
	int i, j, p, t;

re:	if (n < 12) {
		for (i = 1; i < n; i++) {
			for (t = a[i], j = i - 1; j >= 0 && a[j] > t; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
		}
		return;
	}

	for (i = 0, j = n - 1, p = a[n >> 1];;) {
		while (a[i] < p) i++;
		while (a[j] > p) j--;

		if (i >= j)
			break;

		t = a[i];
		a[i++] = a[j];
		a[j--] = t;
	}

	if ((n - i) > 1)
		isort(a + i, n - i);

	n = i;
	goto re;
}

static void insert(int k)
{
	int a, b, c;

	for (a = 0, b = total - 1; a <= b;) {
		count[c = (a + b) >> 1]++;

		if (k < key[c])
			b = c - 1;
		else if (k > key[c])
			a = c + 1;
		else
			return;
	}
}

static int find_less(int k)
{
	int a, b, c, r;

	for (r = 0, a = 0, b = total - 1; a <= b;) {
		c = (a + b) >> 1;
		if (k < key[c]) {
			b = c - 1;
		} else if (k > key[c]) {
			r += count[c];
			a = c + 1;
			if (a <= b) r -= count[(a + b) >> 1];
		} else {
			b = c - 1;
			if (a <= b) r += count[(a + b) >> 1];
			break;
		}
	}

	return r;
}

static int find_greater(int k)
{
	int a, b, c, r;

	for (r = 0, a = 0, b = total - 1; a <= b;) {
		c = (a + b) >> 1;
		if (k < key[c]) {
			r += count[c];
			b = c - 1;
			if (a <= b) r -= count[(a + b) >> 1];
		} else if (k > key[c]) {
			a = c + 1;
		} else {
			a = c + 1;
			if (a <= b) r += count[(a + b) >> 1];
			break;
		}
	}

	return r;
}

int main2()
{
	static int s1[MAXN], s2[MAXN], d[256], dm[256], n, s;
	static char buf[26 * 1048576];
	static pt_t p[MAXN];
	int i, j, k;
	char *inp;

	for (i = 0; i < 256; i++) d[i] = 0;
	for (i = '0'; i <= '9'; i++) d[i] = 1;

	for (i = 0; i < 256; i++) dm[i] = 1;
	for (i = '0'; i <= '9'; i++) dm[i] = 0;
	dm['-'] = 0;

	read(0, inp = buf, sizeof(buf));

#define R(x) \
	{ while (dm[*inp]) inp++; \
	  if (*inp == '-') { \
	    inp++; for (x = *inp++ - '0'; d[*inp];) x = x * 10 + *inp++ - '0'; \
	    x = -x; \
	  } else { \
	    for (x = *inp++ - '0'; d[*inp];) x = x * 10 + *inp++ - '0'; \
	  } \
	}

	for (;;) {
		R(n);
		if (n < 1) break;

		for (i = 0; i < n; i++) {
			R(j); p[i].x = j;
			R(j); p[i].y = j;
		}

		ysort(p, n);

		for (key[0] = j = p[0].y, k = 1, i = 1; i < n; i++)
			if (p[i].y != j) key[k++] = j = p[i].y;
		total = k;

		xsort(p, n);

		for (i = 0; i < total; i++)
			count[i] = 0;

		for (i = 0; i < n; i = j) {
			for (j = i; j < n && p[j].x == p[i].x; j++) {
				s1[j] = find_less(p[j].y);
				s2[j] = find_greater(p[j].y);
			}

			for (j = i; p[j].x == p[i].x; j++)
				insert(p[j].y);
		}

		for (i = 0; i < total; i++)
			count[i] = 0;

		for (i = n - 1; i >= 0; i = j) {
			for (j = i; j >= 0 && p[j].x == p[i].x; j--) {
				s2[j] += find_less(p[j].y);
				s1[j] += find_greater(p[j].y);
			}

			for (j = i; j >= 0 && p[j].x == p[i].x; j--)
				insert(p[j].y);
		}

		for (k = 0, i = 0; i < n; i = j, k++) {
			s1[k] = s1[i];
			s2[k] = s2[i];
			for (j = i + 1; j < n && p[j].x == p[i].x; j++) {
				if (s1[j] < s1[k]) s1[k] = s1[j];
				if (s2[j] > s2[k]) s2[k] = s2[j];
			}
		}

		for (s = s1[0], i = 0; i < k; i++)
			if (s1[i] > s) s = s1[i];

		for (j = 0, i = 0; i < k; i++)
			if (s1[i] == s) key[j++] = s2[i];

		isort(key, j);

		printf("Stan: %d; Ollie:", s);
		for (i = 0; i < j; i++)
			if (i == 0 || key[i - 1] != key[i])
				printf(" %d", key[i]);
		printf(";\n");
	}

	exit(0);
}
