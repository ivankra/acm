#include <stdio.h>
#include <stdlib.h>

#define MAXX 11000

static int sky[MAXX];

int main()
{
	int i, j, t, r;
	int t_l, t_h, t_r;

	for (i = 0; i < MAXX; i++)
		sky[i] = 0;

	r = 0;

	while (scanf("%d %d %d", &t_l, &t_h, &t_r) >= 3) {
		for (j = t_l; j < t_r; j++)
			if (sky[j] < t_h) sky[j] = t_h;
		if (t_r > r)
			r = t_r;
	}

	for (i = 0; i < r;) {
		for (t = sky[i++]; i < r && sky[i] == t; i++);
		printf("%d ", i);

		if (i < r)
			printf("%d ", sky[i]);
	}
	printf("0\n");

	return 0;
}
