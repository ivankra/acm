#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int wa[65536], wb[65536], mb[65536], n, len, t;

int main()
{
	int i, j, k;

	memset(mb, 0, sizeof(mb));

	for (t = 1; ; t++) {
		if (t > 1 && n == 0 && len == 0) break;
		if (scanf("%d %d", &len, &n) != 2) break;

		assert(len <= 16);

		if (n > (1 << len)) {
			for (i = 0; i < n; i++)
				for (j = 0; j < len && (k = getchar()) != EOF;)
					if (k == '0' || k == '1' || k == '*') j++;
			printf("NO\n");
			continue;
		}

		for (i = 0; i < n; i++) {
			wa[i] = wb[i] = 0;
			for (j = 0; j < len && (k = getchar()) != EOF;) {
				if (k == '0' || k == '1') {
					wa[i] = (wa[i] << 1) | (k - '0');
					wb[i] = (wb[i] << 1) | 1;
					j++;
				} else if (k == '*') {
					wa[i] <<= 1;
					wb[i] <<= 1;
					j++;
				}
			}
		}

		for (i = 0; i < n; i++) {
			if (mb[wb[i]] == t) break;
			mb[wb[i]] = t;
		}

		if (i < n) {
			printf("NO\n");
			continue;
		}

		if (mb[0] == t) {
			k = 1 << len;
		} else {
			for (i = 1 << len, k = 0; i--;)
				for (j = 0; j < n; j++)
					if ((i & wb[j]) == wa[j]) { k++; break; }
		}

		printf("YES %d\n", k);
	}

	return 0;
}
