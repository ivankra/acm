#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 32
typedef struct { int a[N]; } num;

void get(num *x)
{
	int d[N], i, c;

	memset(x, 0, sizeof(num));

	while ((c = getchar()) != EOF && !isdigit(c));
	while (c == '0') c = getchar();
	if (c == EOF) return;

	for (i = 0; c != EOF && isdigit(c); c = getchar())
		d[i++] = c - '0';

	for (c = 0; i-- > 0;)
		x->a[c++] = d[i];
}

void add(num *z, num *x)
{
	int i, c;
	for (c = i = 0; i < N; i++, c /= 10)
		z->a[i] = (c += z->a[i] + x->a[i]) % 10;
}

void p(num *x)
{
	int i;
	for (i = N - 1; i >= 1 && x->a[i] == 0; i--);
        while (i >= 0) putchar('0' + x->a[i--]);
}

int main()
{
	int i, j, n, d, t;
	num x, s;

	for (t = 1; scanf("%d %d", &n, &d) == 2 && n > 0; t++) {
		memset(&s, 0, sizeof(s));

		while (n-- > 0) {
			get(&x);
			add(&s, &x);
		}

		printf("Bill #%d costs ", t);
		p(&s);

		for (i = N, j = 0; i-- > 0;) {
			j = j * 10 + s.a[i];
			s.a[i] = j / d;
			j %= d;
		}

		printf(": each friend should pay ");
		p(&s);
		printf("\n\n");
	}

	return 0;
}
