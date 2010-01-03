#include <stdio.h>

static void print(int s, int n, int h)
{
	int k, r;

	if (n <= 0) return;

	if (n == 1) {
		printf(" %d", s);
		return;
	}

	r = (1 << (h - 1)) - 1;
	if (r >= n) r = n - 1;

	k = n - r - 1;

	printf(" %d", s + k);

	print(s, k, h - 1);
	print(s + k + 1, r, h - 1);
}

int main()
{
	int t, n, h;

	for (t = 1; scanf("%d %d", &n, &h) == 2 && (n | h) != 0; t++) {
		if (n >= (1 << h)) {
			printf("Case %d: Impossible.\n", t);
		} else {
			printf("Case %d:", t);
			print(1, n, h);
			printf("\n");
		}
	}

	return 0;
}
