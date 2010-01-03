#include <stdio.h>
#include <string.h>

int main()
{
	static int a[8][8], s[128], m[8][8];
	int i, j, k, f, t;

	scanf("%d", &t);

	while (t-- > 0) {
		memset(a, 0, sizeof(a));
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				if (i == 2 && j == 2)
					a[i][j] = 0;
				else
					scanf("%d", &a[i][j]);
			}
		}

		for (i = 0; i < 75; i++)
			scanf("%d", &s[i]);

		memset(m, 0, sizeof(m));
		m[2][2] = 1;

		for (k = 0; k < 74; k++) {
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++) {
					if (a[i][j] == s[k]) {
						m[i][j] = 1;
						i = 5;
						break;
					}
				}
			}

			f = 0;

			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++)
					if (m[i][j] == 0) break;
				if (j == 5) { f = 1; break; }
			}
			if (f) break;

			for (i = 0; i < 5; i++) {
				for (j = 0; j < 5; j++)
					if (m[j][i] == 0) break;
				if (j == 5) { f = 1; break; }
			}
			if (f) break;

			for (i = 0; i < 5; i++)
				if (m[i][i] == 0) break;
			if (i == 5) break;

			for (i = 0; i < 5; i++)
				if (m[i][4 - i] == 0) break;
			if (i == 5) break;
		}

		printf("BINGO after %d numbers announced\n", k+1);
	}

	return 0;
}
