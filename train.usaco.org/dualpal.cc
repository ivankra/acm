/*
ID: infnty1
PROB: dualpal
LANG: C++
*/
#include <stdio.h>

int rev(int n, int b) { int r = 0; while (n > 0) r=r*b+(n%b),n/=b; return r; }

int main()
{
	int i, j, n, s;

	freopen("dualpal.in", "r", stdin);
	freopen("dualpal.out", "w", stdout);

	scanf("%d %d", &n, &s);

	for (s++; n > 0; s++)
		for (j = 0, i = 2; i <= 10; i++)
			if (s==rev(s,i) && ++j==2) { printf("%d\n", s); n--; break; }

	return 0;
}
