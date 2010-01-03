#include <stdio.h>

void rot(int a[], char *s)
{
	int t = a[*s];

	for (; s[1]; s++)
		a[*s] = a[s[1]];

	a[*s] = t;
}

int main()
{
	char s[1024];
	int a[256], i, n;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (i = '1'; i <= '6'; i++) a[i] = i;

		while (n-- > 0 && scanf(" %s", s) == 1) {
			s[0] |= 0x20;
			if (s[0] == 'n')
				rot(a, "2156");
			else if (s[0] == 's')
				rot(a, "6512");
			else if (s[0] == 'w')
				rot(a, "3146");
			else
				rot(a, "6413");
		}

		printf("%c\n", a['1']);
	}

	return 0;
}
