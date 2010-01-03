#include <cstdio>

int main()
{
	int p, e, i, d, k;

	scanf("%d %d %d %d", &p, &e, &i, &d);
	p = 23 - (p % 23);
	e = 28 - (e % 28);
	i = 33 - (i % 33);

	for (d++, k = 1;; d++, k++)
		if (((p + d) % 23) == 0 && ((e + d) % 28) == 0 &&
		    ((i + d) % 33) == 0)
			break;
	printf("%d\n", k);
}
