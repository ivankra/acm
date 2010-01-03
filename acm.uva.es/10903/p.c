#include <stdio.h>
#include <string.h>

int won[1024], lost[1024], n, k, t, x, y;
char s1[1024], s2[1024];

int beats[32][32];

int main()
{
	int i, j;

#define B(C1, C2) beats[C1 - 'a'][C2 - 'a'] = 1
	B('p', 'r');
	B('s', 'p');
	B('r', 's');
#undef B

	for (t = 0; scanf("%d %d", &n, &k) == 2 && n > 0; t++) {
		if (t) printf("\n");

		for (i = 1; i <= n; i++) won[i] = 0;
		for (i = 1; i <= n; i++) lost[i] = 0;

		for (k *= (n*(n-1))>>1; k-- > 0;) {
			scanf("%d %s %d %s", &x, s1, &y, s2);

			i = (s1[0] | 0x20) - 'a';
			j = (s2[0] | 0x20) - 'a';

			won[x] += beats[i][j];
			lost[y] += beats[i][j];

			won[y] += beats[j][i];
			lost[x] += beats[j][i];
		}

		for (i = 1; i <= n; i++)
			if ((won[i] + lost[i]) == 0)
				printf("-\n");
			else
				printf("%.3f\n", (double)won[i] / (double)(won[i] + lost[i]));
	}

	return 0;
}
