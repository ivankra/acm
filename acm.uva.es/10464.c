#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NDIG 2500

typedef struct {
	int d[NDIG], s, e;
} num_t;

void shift(num_t *x, int s)
{
	int i, j;

	x->e -= s;

	for (i = NDIG - 1 - s, j = NDIG - 1; i >= 0;)
		x->d[j--] = x->d[i--];

	while (j >= 0)
		x->d[j--] = 0;
}

void denorm(num_t *x, num_t *y)
{
	if (x->e > y->e)
		shift(x, x->e - y->e);
	else if (y->e > x->e)
		shift(y, y->e - x->e);
}

void norm(num_t *x)
{
	int i, j;

	for (i = NDIG; i > 0 && x->d[i - 1] == 0; i--);

	if (i == 0) {
		x->s = 1;
		x->e = 0;
		return;
	}

	for (i = 0; i < NDIG && x->d[i] == 0; i++);

	if (i == 0)
		return;

	x->e += i;

	for (j = 0; i < NDIG;)
		x->d[j++] = x->d[i++];

	while (j < NDIG)
		x->d[j++] = 0;
}

void i_add(num_t *z, num_t *x, num_t *y)
{
	int i, c;

	for (c = 0, i = 0; i < NDIG; i++) {
		c += x->d[i] + y->d[i];
		z->d[i] = c % 10;
		c /= 10;
	}

	z->e = x->e;
}

int i_cmp(num_t *x, num_t *y)
{
	int i;

	for (i = NDIG - 1; i >= 0; i--)
		if (x->d[i] != y->d[i]) return (x->d[i] - y->d[i]);

	return 0;
}

void i_sub(num_t *z, num_t *x, num_t *y)
{
	int i, c;

	if (i_cmp(x, y) < 0) {
		i_sub(z, y, x);
		z->s = -1;
		return;
	}

	z->s = 1;
	z->e = x->e;

	for (c = 0, i = 0; i < NDIG; i++) {
		c = x->d[i] - y->d[i] - c;

		if (c >= 0) {
			z->d[i] = c;
			c = 0;
		} else {
			z->d[i] = c + 10;
			c = 1;
		}
	}
}

void add(num_t *z, num_t *x, num_t *y)
{
	denorm(x, y);

	if (x->s == 1 && y->s == 1) {
		i_add(z, x, y);
		z->s = 1;
	} else if (x->s < 0 && y->s < 0) {
		i_add(z, x, y);
		z->s = -1;
	} else if (x->s > 0 && y->s < 0) {
		i_sub(z, x, y);
	} else {
		i_sub(z, y, x);
	}

	norm(x);
	norm(y);
	norm(z);
}

int get(num_t *x)
{
	static int d[NDIG], k;
	int i, c, f;

	x->s = 1;
	x->e = 0;
	for (i = 0; i < NDIG; i++)
		x->d[i] = 0;

	while ((c = getchar()) != EOF)
		if (isdigit(c) || c == '.' || c == '-') break;

	if (c == EOF)
		return 0;

	if (c == '-') {
		x->s = -1;
		c = getchar();
	}

	for (f = k = 0; c != EOF && (isdigit(c) || c == '.'); c = getchar()) {
		if (isdigit(c)) {
			d[k++] = c - '0';
			if (f) x->e--;
		} else if (c == '.') {
			f = 1;
		}
	}

	if (c != EOF)
		ungetc(c, stdin);

	for (i = 0; k > 0;)
		x->d[i++] = d[--k];

	norm(x);

	return 1;
}

void print(num_t *x)
{
	int i, k;

	norm(x);

	if (x->s < 0)
		putchar('-');

	for (k = NDIG; k > 0 && x->d[k - 1] == 0; k--);

	if (x->e >= 0) {
		for (i = NDIG - 1; i > 0 && x->d[i] == 0; i--);

		while (i >= 0)
			putchar(x->d[i--] + '0');

		for (i = 0; i < x->e; i++)
			putchar('0');

		printf(".0\n");
		return;
	}

	if (k <= (-x->e)) {
		printf("0.");
		for (i = -x->e - k; i > 0; i--)
			putchar('0');
	} else {
		for (i = k + x->e; i-- > 0;)
			putchar(x->d[--k] + '0');
		putchar('.');
	}

	while (k > 0)
		putchar(x->d[--k] + '0');
	putchar('\n');
}

int main()
{
	num_t x, y, z;
	int t;

	for (scanf("%d", &t); t-- > 0 && get(&x) == 1 && get(&y) == 1;) {
		add(&z, &x, &y);
		print(&z);
	}

	return 0;
}
