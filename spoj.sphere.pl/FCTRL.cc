#include <stdio.h>

int main()
{
	int t, r, n;
	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (r = 0; n >= 5;) r += (n /= 5);
		printf("%d\n", r);
	}
	return 0;
}
