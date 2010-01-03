#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { unsigned n, a[126]; char *str; } num_t;

void set(num_t *x, unsigned a0)
{
	x->a[0] = a0;
	x->n = a0 ? 1 : 0;
}

int cmp(num_t *x, num_t *y)
{
	int i;
	if (x->n != y->n) return (x->n - y->n);
	for (i = x->n - 1; i >= 0; i--)
		if (x->a[i] != y->a[i]) return (x->a[i] - y->a[i]);
	return 0;
}

int qscmp(const void *p, const void *q) { return cmp((num_t *)p, (num_t *)q); }

void add(num_t *z, num_t *x, num_t *y)
{
	unsigned i, c;

	if (x->n < y->n) {
		num_t *t = x; x = y; y = t;
	}

	/* assert x->n >= y->n */

	for (i = 0, c = 0; i < y->n; i++, c >>= 16)
		z->a[i] = (c += x->a[i] + y->a[i]) & 0xFFFF;

	for (; i < x->n; i++, c >>= 16)
		z->a[i] = (c += x->a[i]) & 0xFFFF;

	z->n = x->n;
	if (c) z->a[z->n++] = c;
}

void muladd(num_t *x, unsigned m, unsigned c)
{
	unsigned i;

	for (i = 0; i < x->n; i++, c >>= 16)
		x->a[i] = (c += x->a[i] * m) & 0xFFFF;

	if (c) x->a[x->n++] = c;
}

void get(num_t *x)
{
	static char buf[65536];
	char *p;
	int i, j;

	scanf(" %[0-9]", buf);
	set(x, 0);

	x->str = strdup(buf);

	i = 0; j = 1;

	for (p = buf; *p; p++) {
		i = i * 10 + *p - '0';
		j *= 10;

		if (j == 10000) {
			muladd(x, j, i);
			i = 0; j = 1;
		}
	}

	if (j > 1 || i != 0)
		muladd(x, j, i);
}

int main()
{
	static num_t s[1024], w;
	int i, j, n;

/*	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
*/
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		get(&s[i]);
	qsort(s, n, sizeof(s[0]), &qscmp);
/*
printf("sizeof s[0]=%d\n",sizeof(s[0])); 
for (i = 0; i < n; i++) printf("%d   %s\n", i, s[i].str);
*/

	for (i = 0; i < n; i++) {
		for (j = i + 1; j < (n - 1); j++) {
			add(&w, &s[i], &s[j]);
			if (cmp(&w, &s[j+1]) > 0) {
				printf("%s %s %s", s[i].str, s[j].str, s[j+1].str);
				return 0;
			}
		}
	}

	printf("0 0 0\n");

	return 0;
}
