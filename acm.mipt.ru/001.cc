#include <cstdio>

int main()
{
	int r, x;
	scanf("%d", &r);
	while (scanf("%d", &x) == 1)
		if (x > r) r = x;
	printf("%d\n", r);
}
