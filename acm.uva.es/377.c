#include <stdio.h>

int get(char *s)
{
	int r;

	for (r = 0; *s; s++) {
		if (*s == 'V')
			r <<= 2;
		else if (*s == 'U')
			r = (r << 2) + 1;
		else if (*s == 'C')
			r = (r << 2) + 2;
		else if (*s == 'D')
			r = (r << 2) + 3;
	}

	return r;
}

int main()
{
	static char s1[1024], s2[1024];
	int i, t, x, y;

	printf("COWCULATIONS OUTPUT\n");

	for (scanf("%d", &t); t-- > 0 && scanf(" %s %s", s1, s2) == 2;) {
		x = get(s1);
		y = get(s2);

		for (i = 0; i < 3 && scanf(" %s", s1) == 1; i++) {
			if (s1[0] == 'A')
				y += x;
			else if (s1[0] == 'R')
				y >>= 2;
			else if (s1[0] == 'L')
				y <<= 2;
		}

		scanf(" %s", s1);
		printf((get(s1) == y) ? "YES\n" : "NO\n");
	}

	printf("END OF OUTPUT\n");
	return 0;
}
