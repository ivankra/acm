#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int n, t, s;
	int a[1];
} heap_t;

heap_t *newheap(int s, int t)
{
	heap_t *h = (heap_t *)malloc(sizeof(heap_t) + s * sizeof(int));
	h->n = 0;
	h->s = s;
	h->t = t;
	return h;
}

void add(heap_t *h, int k)
{
	int i;

	if (h->t == '<') {
		for (i = ++h->n; i > 1 && h->a[i >> 1] > k; i >>= 1)
			h->a[i] = h->a[i >> 1];
	} else {
		for (i = ++h->n; i > 1 && h->a[i >> 1] < k; i >>= 1)
			h->a[i] = h->a[i >> 1];
	}

	h->a[i] = k;
}

int get(heap_t *h)
{
	int i, j, k;

	if (h->n-- == 1)
		return h->a[1];

	h->a[0] = h->a[1];
	h->a[1] = h->a[h->n + 1];

	if (h->t == '<') {
		for (i = 1; (j = i << 1) <= h->n;) {
			k = (h->a[j] < h->a[i]) ? j : i;
			if ((j + 1) <= h->n && h->a[j + 1] < h->a[k]) k = j + 1;
			if (k == i) break;
			j = h->a[i];
			h->a[i] = h->a[k];
			h->a[i = k] = j;
		}
	} else {
		for (i = 1; (j = i << 1) <= h->n;) {
			k = (h->a[j] > h->a[i]) ? j : i;
			if ((j + 1) <= h->n && h->a[j + 1] > h->a[k]) k = j + 1;
			if (k == i) break;
			j = h->a[i];
			h->a[i] = h->a[k];
			h->a[i = k] = j;
		}
	}

	return h->a[0];
}

int main()
{
	heap_t *low = newheap(16384, '>'), *up = newheap(16384, '<');
	int m[2], k, x;

	for (k = 0; scanf("%d", &x) == 1;) {
		if (k == 0) {
			m[k++] = x;
		} else if (k == 1) {
			if (x <= m[0]) {
				add(low, x);
				m[1] = m[0];
				m[0] = get(low);
			} else {
				add(up, x);
				m[1] = get(up);
			}
			k = 2;
		} else {
			if (x <= m[0]) {
				add(low, x);
				add(up, m[1]);
			} else if (x >= m[1]) {
				add(up, x);
				add(low, m[0]);
				m[0] = m[1];
			} else {
				add(low, m[0]);
				add(up, m[1]);
				m[0] = x;
			}
			k = 1;
		}

		if (k == 1)
			printf("%d\n", m[0]);
		else
			printf("%d\n", (m[0] + m[1]) >> 1);
	}

	return 0;
}
