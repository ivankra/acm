#include <stdio.h>

int pos[16];

void queen(int row)
{
	int i, j;

	if (row > 7) {
		for (i = 0; i < 8; i++)
			printf(i ? ", %d" : "\t{ %d", i * 8 + pos[i]);
		printf(" },\n");
		return;
	}

	for (i = 0; i <= 7; i++) {
		for (j = 0; j < row; j++) {
			if (pos[j] == i) break;
			if ((pos[j] + row - j) == i) break;
			if ((pos[j] - row + j) == i) break;
		}
		if (j < row) continue;

		pos[row] = i;
		queen(row + 1);
	}
}

int main()
{
	int i;

	queen(0);

	return 0;
}
