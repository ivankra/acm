#include <stdio.h>

int t, r[] = {0,2,7,5,30,169,441,1872,7632,1740,93313,459901,1358657,2504881};

int main()
{
	while (scanf("%d", &t) == 1 && t != 0)
		printf("%d\n", r[t]);

	return 0;
}
