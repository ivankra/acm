#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	printf("%d\n", (n/6)*4 + "112334"[n%6] - '1');
	return 0;
}
