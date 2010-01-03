#include <stdio.h>
#include <string.h>

#define S 24

typedef struct { int a[32], n; } num;

void set(num *z, int a) { z->a[0] = a; z->n = a ? 1 : 0; }

void add(num *x, num *y)
{
	int i, c;
	while (x->n < y->n) x->a[x->n++] = 0;
	for (c=i=0; i<y->n; i++, c>>=S) x->a[i]=(c+=x->a[i]+y->a[i]) & ((1<<S)-1);
	for (; c && i < x->n; i++, c>>=S) x->a[i] = (c += x->a[i]) & ((1<<S)-1);
	if (c) x->a[x->n++] = c;
}

void sub(num *x, num *y)
{
	int i, c;
	for (i = c = 0; i < y->n; i++)
		if ((x->a[i] -= y->a[i]+c) < 0) { x->a[i]+=1<<S; c=1; } else c=0;
	if (c) { for (;; i++) if (x->a[i]--) break; else x->a[i] = (1<<S)-1; }
	while (x->n > 0 && x->a[x->n-1] == 0) x->n--; }

void prn(num *x)
{
	static char s[1024];
	int i, r, k;

	for (k = 0; x->n > 0;) {
		for (r = 0, i = x->n-1; i >= 0; i--) {
			r = (r << S) | x->a[i];
			x->a[i] = r / 10;
			r %= 10;
		}
		s[k++] = r + '0';
		while (x->n > 0 && x->a[x->n-1] == 0) x->n--;
	}

	while (k-- > 0) putchar(s[k]);
	printf("\n");
}

num p[5001];

int main()
{
	int n, k, t;

	set(&p[0], 1);
	for (n = 1; n <= 5000; n++) {
		set(&p[n], 0);
		for (k = 1; (t = k*(3*k-1)/2) <= n; k++) {
			if (k & 1) {
				add(&p[n], &p[n-t]);
				if ((t+=k) <= n) add(&p[n], &p[n-t]);
			} else {
				sub(&p[n], &p[n-t]);
				if ((t+=k) <= n) sub(&p[n], &p[n-t]);
			}
		}
	}

	while (scanf("%d", &n) == 1) prn(&p[n]);

	return 0;
}
