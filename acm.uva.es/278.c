#include <stdio.h>

int main()
{
	char s[16];
	int m, n, t;

	for (scanf("%d",&t); t-- > 0 && scanf(" %[a-zA-Z] %d%d",s,&m,&n)==3;) {
		if (s[0] == 'r' || s[0] == 'Q')
			printf("%d\n", (m < n) ? m : n);
		else if (s[0] == 'K')
			printf("%d\n", ((m + 1) >> 1) * ((n + 1) >> 1));
		else
			printf("%d\n", (m * n + 1) >> 1);
	}

	return 0;
}
