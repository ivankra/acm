#include <stdio.h>

int list[] = {
	2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, 97, 113, 131, 199, 311,
	337, 373, 733, 919, 991, 0
};

int main()
{
	int i, n, u;

	while (scanf("%d", &n) == 1 && n > 0) {
		if (n > 991) {
			printf("0\n");
			continue;
		}

		for (u = 1; u <= n; u *= 10);

		for (i = 0; list[i]; i++)
			if (list[i] > n && list[i] < u) {
				printf("%d\n", list[i]);
				break;
			}

		if (list[i] == 0)
			printf("0\n");
	}

	return 0;
}
