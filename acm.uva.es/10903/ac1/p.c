#include <stdio.h>
#include <string.h>
#include <assert.h>

int won[1024], lost[1024], n, k, t, x, y;
char s1[1024], s2[1024];

int main()
{
	int i, j;

	for (t = 0; scanf("%d %d", &n, &k) == 2 && n > 0; t++) {
		if (t) printf("\n");

		memset(won, 0, sizeof(won));
		memset(lost, 0, sizeof(lost));

		for (i = k*n*(n-1)/2; i-- > 0;) {
			j = scanf("%d %s %d %s", &x, s1, &y, s2);
			assert(j == 4);

			s1[0] |= 0x20; s2[0] |= 0x20;

			if (s1[0] == 'p' && s2[0] == 'r')
				won[x]++, lost[y]++;
			else if (s1[0] == 's' && s2[0] == 'p')
				won[x]++, lost[y]++;
			else if (s1[0] == 'r' && s2[0] == 's')
				won[x]++, lost[y]++;

			else if (s1[0] == 'r' && s2[0] == 'p')
				won[y]++, lost[x]++;
			else if (s1[0] == 'p' && s2[0] == 's')
				won[y]++, lost[x]++;
			else if (s1[0] == 's' && s2[0] == 'r')
				won[y]++, lost[x]++;
		}

		for (i = 1; i <= n; i++)
			if ((won[i] + lost[i]) == 0)
				printf("-\n");
			else
				printf("%.3f\n", (double)won[i] / (double)(won[i] + lost[i]));
	}

	return 0;
}
