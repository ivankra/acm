#include <stdio.h>

char *suits[4] = { "Clubs", "Diamonds", "Hearts", "Spades" };

char *values[13] = {
	"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen",
	"King", "Ace"
};

int main()
{
	static char names[52][64], buf[1024];
	static int shuf[128][52], temp1[52], temp2[52], n, t;
	int i, j, *p, *q;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 13; j++)
			sprintf(names[(i * 13) + j], "%s of %s",
				values[j], suits[i]);

	scanf("%d", &t);

	while (t-- > 0 && scanf("%d ", &n) == 1) {
		for (i = 1; i <= n; i++) {
			for (j = 0; j < 52; j++) {
				scanf(" %d ", &shuf[i][j]);
				shuf[i][j]--;
			}
		}

		for (i = 0, p = temp1, q = temp2; i < 52; i++)
			p[i] = i;

		while (gets(buf) && sscanf(buf, "%d", &n) == 1) {
			for (i = 0; i < 52; i++)
				q[i] = p[shuf[n][i]];

			p = q;
			q = (q == temp1) ? temp2 : temp1;
		}

		for (i = 0; i < 52; i++)
			printf("%s\n", names[p[i]]);

		if (t > 0)
			printf("\n");

	}

	return 0;
}
