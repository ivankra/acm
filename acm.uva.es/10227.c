#include <stdio.h>
#include <stdlib.h>

#define MAXT 128
#define MAXP 128

static char data[MAXP][MAXT];
static int var[MAXP];

int main()
{
	static int t, p, n, a, b;
	static char line[256];
	int i, j, k, r;

	scanf("%d", &n);
	while (n-- > 0) {
		if (scanf("%d %d\n", &p, &t) < 2)
			break;

		memset(data, '\0', sizeof(data));

		for (i = 0;;) {
			if (fgets(line, sizeof(line), stdin) == NULL)
				break;

			if (sscanf(line, "%d %d", &a, &b) >= 2) {
				data[a - 1][b - 1] = 1;
				i++;
			} else if (i != 0) {
				break;
			}
		}

		for (i = 0; i < p; i++)
			var[i] = 0;

		for (i = 0, r = 0; i < p; i++) {
			if (var[i]) continue;
			var[i] = 1;
			for (r++, j = i + 1; j < p; j++) {
				if (var[j]) continue;
				for (k = 0; k < MAXT; k++)
					if (data[j][k] != data[i][k]) break;
				if (k >= t) var[j] = 1;
			}
		}

		printf("%d\n", r);

		if (n != 0)
			printf("\n");
	}

	return 0;
}
