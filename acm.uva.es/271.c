#include <stdio.h>

static int check(char *s)
{
	int k;

	for (k = 1; *s; s++) {
		if (*s == 'C' || *s == 'D' || *s == 'E' || *s == 'I') {
			if (k == 0) return 0;
			k++;
		} else if (*s >= 'p' && *s <= 'z') {
			if (k == 0) return 0;
			k--;
		} else if (*s == 'N') {
			if (k == 0) return 0;
		} else {
			/* ignore */
		}
	}

	return (k == 0);
}

int main()
{
	static char buf[1024];

	while (gets(buf))
		printf(check(buf) ? "YES\n" : "NO\n");

	return 0;
}
