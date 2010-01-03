#include <stdio.h>
#include <string.h>

int main()
{
	static int m[64][64];
	static char x[4], y[4];
	register int i, j, k;

	for (i = 0; i < 64; i++) {
		for (j = 0; j < 64; j++)
			m[i][j] = 6;
		m[i][i] = 0;
	}

#define MOVE(R,C) if((R)>=0 && (R)<8 && (C)>=0 && (C)<8) m[i][((R)<<3)+(C)]=1;
	for (j = 0, i = 0; j < 8; j++) {
		for (k = 0; k < 8; k++, i++) {
			MOVE(j - 2, k - 1);
			MOVE(j - 2, k + 1);
			MOVE(j - 1, k - 2);
			MOVE(j - 1, k + 2);
			MOVE(j + 1, k - 2);
			MOVE(j + 1, k + 2);
			MOVE(j + 2, k - 1);
			MOVE(j + 2, k + 1);
		}
	}
#undef MOVE

	for (k = 0; k < 64; k++) {
		for (i = 0; i < 64; i++) {
			for (j = 0; j < i; j++) {
				register int t = m[i][k] + m[k][j];
				if (m[i][j] > t)
					m[i][j] = m[j][i] = t;
			}
		}
	}

	while (scanf(" %2[a-hA-H1-8] %2[a-hA-H1-8]", x, y) == 2) {
		i = ((x[1] - '1') << 3) + ((x[0] | 0x20) - 'a');
		j = ((y[1] - '1') << 3) + ((y[0] | 0x20) - 'a');

		printf("To get from %s to %s takes %d knight moves.\n",
		       x, y, m[i][j]);
	}

	return 0;
}
