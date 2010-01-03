#include <stdio.h>

int get(int x)
{
	int h, m, s;

	h = x / 1000000;
	x %= 1000000;

	m = x / 10000;
	x %= 10000;

	s = x / 100;
	x %= 100;

	return (((h * 60 + m) * 60 + s) * 100 + x);

}

int main()
{
	int x;

	while (scanf("%d", &x) == 1)
		printf("%.7d\n", (int)((get(x) * 10000000ULL) / 8640000ULL));

	return 0;
}
