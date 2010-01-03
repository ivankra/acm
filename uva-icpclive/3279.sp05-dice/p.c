#include <stdio.h>

int main()
{
	char s1[1024], s2[1024], s3[1024];
	int i, k, n, m;

	while (scanf(" %s %s %s %d", s1, s2, s3, &n) == 4 && s1[0] != '#') {
		for (i = m = 0; i < n && scanf("%d", &k) == 1; i++)
			if ((((s3[0] | 0x20) == 'e') ? 0 : 1) == (k & 1)) m++;
		printf("%s %d %s %d\n", s1, n - m, s2, m);		
	}
	
	return 0;
}

