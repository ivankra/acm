#include <stdio.h>
#include <string.h>

int n;
char record[1048576];

int winner()
{
	static int pt[256], game_wins[256], set_wins[256];
	char *s;
	int i, j, k;

	memset(pt, 0, sizeof(pt));
	memset(set_wins, 0, sizeof(set_wins));
	memset(game_wins, 0, sizeof(game_wins));

	for (s = record; *s; s++) {
		k = *s - 'A';

		/* rule 1 */
		for (j = -1, i = 0; i < n; i++)
			if (i != k && pt[i] > j) j = pt[i];
		if ((pt[k] == 3 && j <= 2) || (pt[k] == 4)) {
			game_wins[k]++;
			memset(pt, 0, sizeof(pt));

			for (i = 0; i < n; i++) {
				if (game_wins[i] < 6) continue;
				for (j = 0; j < n; j++)
					if (i != j && game_wins[i] < (game_wins[j] + 2)) break;
				if (j >= n) break;
			}
			if (i >= n) continue;

			set_wins[i]++;

			for (j = 0; j < n; j++)
				if (j != i && game_wins[j] != 0) break;
			if (j >= n) set_wins[i]++;

			memset(game_wins, 0, sizeof(game_wins));

			if (set_wins[i] >= 3) {
				return i;
			}

			continue;
		}

		/* rule 3 */
		for (i = 0; i < n && pt[i] != 4; i++);
		if (i < n) {
			pt[i]--;	
			continue;
		}

		pt[k]++;
	}

fprintf(stderr,"unknown\n");
	return 0;
}

int main()
{
	while (scanf("%d %[A-Za-z]", &n, record) == 2) {
		printf("%c\n", winner() + 'A');
	}

	return 0;
}
