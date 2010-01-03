#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
	int n, t, s;
	int a[1];
} heap_t;

/* t: '<' minheap, '>' maxheap */
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

	assert((h->n + 1) < h->s);

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
	int i, n, x;
	heap_t *h = newheap(8192, '<');

	while (scanf("%d", &n) == 1 && n > 0) {
		h->n = 0;
		for (i = 0; i < n && scanf("%d", &x) == 1; i++)
			add(h, x);

		for (x = 0; h->n > 1;) {
			add(h, i = get(h) + get(h));
			x += i;
		}

		printf("%d\n", x);
	}

	return 0;
}
