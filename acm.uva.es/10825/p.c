#include <stdio.h>

int main()
{
	static int a, m, n;

	while (scanf("%d %d", &m, &n) == 2 && (n | m) != 0) {
		if (n < 7) {
			printf("Not found.\n");
			continue;
		}

		if (m == 4 && (n % 5) == 2) {
			a = (n - 2) / 5;
			printf("%d %d %d %d\n",
				a,
				2 * a,
				4 * a + 1,
				3 * a + 1);
		} else if (m == 4 && (n % 5) == 3) {
			a = (n - 3) / 5;
			printf("%d %d %d %d\n",
				a,
				3 * a + 1,
				4 * a + 2,
				2 * a + 1);
		} else if (m == 6 && (n % 7) == 3) {
			a = (n - 3) / 7;
			printf("%d %d %d %d %d %d\n",
				a,
				3 * a + 1,
				2 * a,
				6 * a + 2,
				4 * a + 1,
				5 * a + 2);
		} else if (m == 6 && (n % 7) == 5) {
			a = (n - 5) / 7;
			printf("%d %d %d %d %d %d\n",
				a,
				5 * a + 3,
				4 * a + 2,
				6 * a + 4,
				2 * a + 1,
				3 * a + 2);
		} else {
			printf("Not found.\n");
		}
	}

	return 0;
}
