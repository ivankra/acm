#include <stdio.h>

int main()
{
	int n, s, d;

	for (scanf("%d", &n); n-- > 0 && scanf("%d %d", &s, &d) == 2;) {
		if (s < d || ((s + d) & 1) != 0 || ((s - d) & 1) != 0)
			printf("impossible\n");
		else
			printf("%d %d\n", (s + d) / 2, (s - d) / 2);
	}

	return 0;
}
