#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct {
	char s[32];
	int c[32];
} dict[1024];

int main()
{
	char t[1024];
	int c[32], i, j, k, n, z;

	for (scanf("%d", &z); z-- > 0 && scanf("%d", &n) == 1;) {
		memset(dict, 0, sizeof(dict));
		for (i = 0; i < n; i++) {
			scanf(" %[a-zA-Z]", dict[i].s);
			for (j = 0; dict[i].s[j]; j++)
				dict[i].c[tolower(dict[i].s[j]) - 'a']++;
		}

		while (scanf(" %[a-zA-Z]", t) == 1 && t[0] != 'E') {
			memset(c, 0, sizeof(c));
			for (i = 0; t[i]; i++)
				c[tolower(t[i]) - 'a']++;

			printf("Anagrams for: %s\n", t);

			for (i = k = 0; i < n; i++) {
				if (memcmp(dict[i].c, c, 26 * sizeof(int)) != 0)
					continue;

				printf("  %d) %s\n", ++k, dict[i].s);
			}

			if (k == 0)
				printf("No anagrams for: %s\n", t);
		}

		if (z != 0) printf("\n");
	}

	return 0;
}
