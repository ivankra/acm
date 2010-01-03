#include <stdio.h>
#include <string.h>

int main()
{
	int a[32][4], i, k, n, s;

	while (scanf("%d", &n) == 1 && n > 0) {
		s = (n + 3) / 4;

		memset(a, 0, sizeof(a));

		for (i = 0, k = 1; i < s && k <= n; i++) {
			a[i][1] = k++;
			if (k <= n) a[i][2] = k++;
		}

		for (i = s - 1; i >= 0 && k <= n; i--) {
			a[i][3] = k++;
			if (k <= n) a[i][0] = k++;
		}

		printf("Printing order for %d pages:\n", n);

		for (i = 0; i < s; i++) {
			if (a[i][0] != 0 || a[i][1] != 0) {
				printf("Sheet %d, front: ", i + 1);
				printf(a[i][0] ? "%d" : "Blank", a[i][0]);
				printf(a[i][1] ? ", %d\n" : ", Blank\n", a[i][1]);
			}

			if (a[i][2] != 0 || a[i][3] != 0) {
				printf("Sheet %d, back : ", i + 1);
				printf(a[i][2] ? "%d" : "Blank", a[i][2]);
				printf(a[i][3] ? ", %d\n" : ", Blank\n", a[i][3]);
			}
		}
	}

	return 0;
}
