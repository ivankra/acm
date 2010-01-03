#include <stdio.h>

static int tree(int piles[])
{
	static int x;

	scanf("%d", &x);

	if (x < 0) {
		return 1;
	} else {
		piles[0] += x;
		tree(piles - 1);
		tree(piles + 1);
		return 0;
	}
}

#define MAXW 4096

int main()
{
	static int piles[MAXW], t;
	int i, j;

	for (t = 1; ; t++) {
		for (i = 0; i < MAXW; i++)
			piles[i] = 0;

		if (tree(&piles[MAXW / 2]))
			break;

		printf("Case %d:\n", t);
		for (i = 0, j = 0; i < MAXW; i++)
			if (piles[i] != 0)
				printf(j++ ? " %d" : "%d", piles[i]);
		printf("\n\n");
	}

	return 0;
}
