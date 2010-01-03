#include <stdio.h>

int main()
{
	int r, c, T, n;

	for (scanf("%d", &T); T-- > 0 && scanf("%d", &n) == 1;) {
		for (r = 0; r*(r+1)/2 < n; r++);
		c = n - (r-1)*r/2;

		if (r & 1)
			printf("TERM %d IS %d/%d\n", n, r+1-c, c);
		else
			printf("TERM %d IS %d/%d\n", n, c, r+1-c);
	}

	return 0;
}
