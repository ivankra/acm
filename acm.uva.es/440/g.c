#include <stdio.h>

int sim(int n, int m)
{
	static int a[256];
	int i, j, last;

	for (i = 0; i < n; i++)
		a[i] = 1;

//fprintf(stderr,"{n=%d,m=%d}",n,m);
	a[0] = 0;
	for (i = 0;;) {
		for (j = m;;) {
			if (++i >= n) i = 0;
			if (a[i]) {
				j--;
				if (j == 0) break;
			}
		}

		a[i] = 0;

		for (j = 0; j < n; j++)
			if (a[j]) break;
		if (j >= n) return i;

//fprintf(stderr,"{%d}",i);
	}
}

int find(int n)
{
	int m, l;

	for (m = 1;; m++) {
		l = sim(n, m);
		if (l == 1) return m;
//		fprintf(stderr,"sim[n=%d, m=%d] = %d\n", n, m, l);
	}
}

int main()
{
	int i;

	for (i = 0; i < 150; i++) {
		if (i < 3)
			printf("0,");
		else
			printf("%d,", find(i));
	}

	return 0;
}
