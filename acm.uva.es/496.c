#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
	int n;
	int a[1];
} set_t;

int subset(set_t *x, set_t *s)
{
	int i, j;

	if (x->n >= s->n)
		return 0;

	for (i = 0, j = 0; i < x->n && j < s->n;) {
		while (j < s->n && s->a[j] < x->a[i])
			j++;

		if (j >= s->n || s->a[j++] != x->a[i++])
			return 0;
	}

	return (i >= x->n);
}

int equal(set_t *p, set_t *q)
{
	int i;

	if (p->n != q->n)
		return 0;

	for (i = 0; i < p->n; i++)
		if (p->a[i] != q->a[i]) return 0;

	return 1;
}

int disjoint(set_t *p, set_t *q)
{
	int i, j;

	for (i = 0, j = 0; i < p->n && j < q->n;) {
		while (i < p->n && p->a[i] < q->a[j])
			i++;

		if (p->a[i] == q->a[j++])
			return 0;
	}

	return 1;
}

set_t *sread()
{
	int c, m;
	set_t *s;

	m = 1024;
	s = (set_t *)malloc(sizeof(set_t) + m * sizeof(int));

	for (s->n = 0; (c = getchar()) != EOF && c != '\n';) {
		if (!isdigit(c) && c != '-')
			continue;

		if ((s->n + 4) > m) {
			m *= 2;
			s = (set_t *)realloc(s, sizeof(set_t) + m * sizeof(int));
		}

		ungetc(c, stdin);
		scanf("%d", &s->a[s->n++]);
	}

	if (c == EOF && s->n == 0) {
		free(s);
		return NULL;
	}

	return s;
}

static void msort(int a[], int n, int temp[])
{
	int i, j, h;

	if (n <= 32) {
		for (i = 1; i < n; i++) {
			for (h = a[i], j = i - 1; j >= 0 && a[j] > h; j--)
				a[j + 1] = a[j];
			a[j + 1] = h;
		}
		return;
	}

	h = (n >> 1);
	msort(a, h, temp);
	msort(a + h, n - h, temp);

	for (i = 0, j = h; i < h && j < n;)
		*temp++ = (a[i] < a[j]) ? a[i++] : a[j++];

	while (i < h)
		*temp++ = a[i++];

	while (j < n)
		*temp++ = a[j++];

	for (temp -= n, i = 0; i < n; i++)
		*a++ = *temp++;
}

void sort(int a[], int n)
{
	int *temp;
	temp = (int *)malloc((n + 1) * sizeof(int));
	msort(a, n, temp);
	free(temp);
}

int main()
{
	set_t *a, *b;

	while ((a = sread()) != NULL && (b = sread()) != NULL) {
		sort(a->a, a->n);
		sort(b->a, b->n);

		if (equal(a, b))
			printf("A equals B\n");
		else if (disjoint(a, b))
			printf("A and B are disjoint\n");
		else if (subset(a, b))
			printf("A is a proper subset of B\n");
		else if (subset(b, a))
			printf("B is a proper subset of A\n");
		else
			printf("I'm confused!\n");

		free(b);
		free(a);
	}

	return 0;
}
