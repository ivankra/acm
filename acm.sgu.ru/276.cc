#include <stdio.h>

int main()
{
	int d, p, s;

	scanf("%d %d", &s, &p);

	d = p - s;

	if (d <= 0)
		s = 0;
	else if (d < 300)
		s = 1;
	else if (d < 900)
		s = 2;
	else if (d < 1800)
		s = 3;
	else
		s = 4;

	printf("%d\n", s);
	return 0;
}
