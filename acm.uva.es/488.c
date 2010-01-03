#include <stdio.h>

int main()
{
	static char *lines[10] = {
		"", "1", "22", "333", "4444", "55555", "666666", "7777777",
		"88888888", "999999999"
	};
	static int t, n, h;
	int i, j;

	scanf("%d", &t);
	while (t-- > 0) {
		scanf("%d %d", &h, &n);

		while (n-- > 0) {
			for (i = 1; i <= h; i++)
				printf("%s\n", lines[i]);

			for (i = h - 1; i >= 1; i--)
				printf("%s\n", lines[i]);

			if (n > 0)
				printf("\n");
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}
