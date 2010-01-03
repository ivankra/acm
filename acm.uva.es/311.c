#include <stdio.h>

int main()
{
	int a[8], i, r;

	for (;;) {
		for (i = 1, r = 0; i <= 6 && scanf("%d", &a[i]) == 1; i++)
			r += a[i];
		if (i <= 6 || r == 0) break;

		r = a[6] + a[5] + a[4] + (a[3] + 3) / 4;
		a[1] -= 11 * a[5];
		a[2] -= 5 * a[4];
		switch (a[3] % 4) {
			case 1: a[2] -= 5; a[1] -= 7; break;
			case 2: a[2] -= 3; a[1] -= 6; break;
			case 3: a[2] -= 1; a[1] -= 5; break;
		}

		if (a[2] < 0) {
			a[1] += 4 * a[2];
			a[2] = 0;
		}

		r += (a[2] + 8) / 9;
		if ((a[2] % 9) > 0)
			a[1] -= (9 - (a[2] % 9)) * 4;

		if (a[1] > 0)
			r += (a[1] + 35) / 36;

		printf("%d\n", r);
	}

	return 0;
}
