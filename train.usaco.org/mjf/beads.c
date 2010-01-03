/*
ID: mjf28791
PROG: beads
LANG: C
*/
#include <stdio.h>

int main()
{
	char s[1024];
	int n, x, r, p, k, c;

	freopen("beads.in", "r", stdin);
	freopen("beads.out", "w", stdout);

	scanf("%d %[rbw]", &n, s);

	if (n <= 0) {
		printf("0\n");
		return 0;
	}

	for (p = 0, r = 0; p < n; p++) {
		k = 0;

		for (c = 0, x = p; k < n; x = (x + 1) % n, k++) {
			if (s[x] == 'w')
				continue;
			else if (c == 0)
				c = s[x];
			else if (c != s[x])
				break;
		}

		x = (p + n - 1) % n;
		for (c = 0; k < n; x = (x + n - 1) % n, k++) {
			if (s[x] == 'w')
				continue;
			else if (c == 0)
				c = s[x];
			else if (c != s[x])
				break;
		}

		if (k > r)
			r = k;
	}

	printf("%d\n", r);

	return 0;
}
