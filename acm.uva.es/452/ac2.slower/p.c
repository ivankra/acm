#include <stdio.h>
#include <string.h>

int main()
{
	static int dep[32][32], ndep[32], cost[32], tm[32], done[32], t, f;
	static char buf[1024];
	char *p;
	int i, j, k;

	for (scanf("%d ", &t); t-- > 0;) {
		memset(dep, '\0', sizeof(dep));

		for (i = 0; i < 26; i++)
			tm[i] = cost[i] = ndep[i] = 0;

		for (i = 0; i < 26; i++)
			done[i] = 1;

		for (i = 0; gets(buf);) {
			for (p = buf; *p && (*p < 'A' || *p > 'Z'); p++);

			if (*p == '\0') {
				if (i == 0) continue;
				break;
			}

			k = *p - 'A';

			while (*p && (*p < '0' || *p > '9')) p++;

			for (cost[k] = 0; *p >= '0' && *p <= '9'; p++)
				cost[k] = cost[k] * 10 + *p - '0';

			for (; *p; p++)
				if (*p >= 'A' && *p <= 'Z') {
					dep[k][*p - 'A'] = 1;
					dep[*p - 'A'][k] = -1;
					ndep[k]++;
				}
			i++;

			done[k] = 0;
		}

		do {
			for (f = 0, i = 0; i < 26; i++) {
				if (done[i] || ndep[i] > 0)
					continue;

				for (j = 0, k = 0; j < 26; j++)
					if (dep[i][j] < 0)
						ndep[j]--;
					else if (dep[i][j] > 0 && tm[j] > k)
						k = tm[j];

				tm[i] = k + cost[i];
				done[i] = 1;
				f = 1;
			}
		} while (f);

		for (i = 0, k = 0; i < 26; i++)
			if (tm[i] > k) k = tm[i];

		printf(t ? "%d\n\n" : "%d\n", k);
	}

	return 0;
}
