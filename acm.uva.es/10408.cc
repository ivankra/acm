#include <stdio.h>

int n, k;

int go(int a, int b, int c, int d)
{
	int p=a+c, q=b+d;
	if (q > n) return 0;
	if (go(a,b, p,q)) return 1;
	if (--k == 0) { printf("%d/%d\n", p, q); return 1; }
	return go(p,q, c,d);
}

int main()
{
	while (scanf("%d %d", &n, &k) == 2 && n > 0)
		if (!go(0,1, 1,1)) printf("1/1\n");
	return 0;
}

