#include <stdio.h>
#include <string.h>

char *s[4];

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int find()
{
	int w, h, r, sh0, sh1, sh2, sh3;

	for (r = 0, sh0 = 1; sh0 <= 8; sh0++) {
		for (sh1 = 1; sh1 <= 8; sh1++) {
			if (s[0][sh0] != s[1][sh1])
				continue;

			for (w = 1; (sh1 + w) <= 9; w++) {
				for (sh2 = 1; sh2 <= 8; sh2++) {
					if (s[1][sh1 + w + 1] != s[2][sh2])
						continue;

					for (h = 1; (sh2 + h) <= 9 && (sh0 + h) <= 9; h++) {
						for (sh3 = 1; sh3 <= 8 && (sh3 + w) <= 9; sh3++) {
							if (s[0][sh0 + h + 1] != s[3][sh3])
								continue;

							if (s[2][sh2 + h + 1] != s[3][sh3 + w + 1])
								continue;

							r = max(r, w * h);
						}
					}
				}
			}
		}
	}

	return r;
}

int main()
{
	static char t[4][256];
	int i, j, k, r;

	while (scanf(" %s %s %s %s", t[0], t[1], t[2], t[3]) == 4 && t[0][0] != 'Q') {
		for (r = 0, i = 0; i < 0xFF; i++) {
			for (j = 0; j < 4; j++) {
				s[j] = t[(i >> (2 * j)) & 3];
				for (k = 0; k < j && s[j] != s[k]; k++);
				if (k < j) break;
			}

			if (j == 4)
				r = max(r, find());
		}

		printf("%d\n", r);
	}

	return 0;
}
