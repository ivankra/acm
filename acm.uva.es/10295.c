#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
	char s[32];
	double v;
} dict[1024];

int main()
{
	static char word[1024];
	int i, a, b, c, n, m;
	double sum;

	scanf("%d %d", &m, &n);

	for (i = 0; i < m; i++)
		scanf(" %s %lf", dict[i].s, &dict[i].v);

	qsort(dict, m, sizeof(dict[0]), &strcmp);

	while (n-- > 0) {
		for (sum = 0; scanf(" %s", word) == 1 && word[0] != '.';) {
			for (a = 0, b = m - 1; a <= b;) {
				c = (a + b) >> 1;

				i = strcmp(dict[c].s, word);

				if (i < 0) {
					a = c + 1;
				} else if (i > 0) {
					b = c - 1;
				} else {
					sum += dict[c].v;
					break;
				}
			}
		}

		printf("%.0f\n", sum);
	}

	return 0;
}
