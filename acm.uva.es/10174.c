#include <stdio.h>

void solve1(int x)
{
	int a, b, sign;

	if (x == 0) {
		printf("0 0\n");
		return;
	}

	sign = (x > 0) ? 1 : -1;
	x *= sign;

	if ((x & 3) == 2) {
		printf("Bachelor Number.\n");
		return;
	}

	if (x & 1) {
		b = (x - 1) >> 1;
		a = b + 1;
	} else {
		a = (x >> 2) + 1;
		b = (x >> 2) - 1;
	}

	if (sign > 0)
		printf("%d %d\n", a, b);
	else
		printf("%d %d\n", b, a);
}

int solve2(int a, int b)
{
	int r;

	for (r = 0; a <= b; a++)
		if ((a & 3) == 2) r++;

	return r;
}

int main()
{
	static char s[1024];
	int a, b;

	while (gets(s)) {
		if (sscanf(s, "%d %d", &a, &b) == 1)
			solve1(a);
		else
			printf("%d\n", solve2(a, b));
	}

	return 0;
}
