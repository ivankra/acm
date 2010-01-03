#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char image[3][32], *digits[3] = {
	" _     _  _     _  _  _  _  _ ",
	"| |  | _| _||_||_ |_   ||_||_|",
	"|_|  ||_  _|  | _||_|  ||_| _|"
};

int check(int x, int d)
{
	int i, j, r;

	for (i = r = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (image[i][3 * x + j] == digits[i][3 * d + j])
				continue;

			if (image[i][3 * x + j] != ' ')
				return -1;

			r++;
		}
	}

	return r;
}

int solve()
{
	int d[16], i, j, k, pos, prev, sol;

	for (i = 0; i < 9; i++) {
		for (d[i] = -1, j = 0; j <= 9; j++) {
			if (check(i, j) == 0) {
				d[i] = j;
				break;
			}
		}
	}

	for (i = 0, pos = k = 0; i < 9; i++) {
		if (d[i] < 0) {
			pos = i;
			k++;
		}
	}

	if (k >= 2)
		return -1;

	sol = -1;

	if (k == 1) {
		for (d[pos] = 0; d[pos] <= 9; d[pos]++) {
			if (check(pos, d[pos]) < 0)
				continue;

			for (i = 0, j = 0; i < 9; i++)
				j += (9 - i) * d[i];

			if ((j % 11) != 0)
				continue;

			for (i = 0, j = 0; i < 9; i++)
				j = j * 10 + d[i];

			if (sol >= 0 && sol != j)
				return -2;

			sol = j;
		}

		return sol;
	}

	for (i = 0, j = 0; i < 9; i++)
		j += (9 - i) * d[i];

	if ((j % 11) == 0) {
		for (i = 0, sol = 0; i < 9; i++)
			sol = sol * 10 + d[i];
		return sol;
	}

	for (pos = 0; pos < 9; pos++) {
		prev = d[pos];

		for (d[pos] = 0; d[pos] <= 9; d[pos]++) {
			if (check(pos, d[pos]) < 0)
				continue;

			for (i = 0, j = 0; i < 9; i++)
				j += (9 - i) * d[i];

			if ((j % 11) != 0)
				continue;

			for (i = 0, j = 0; i < 9; i++)
				j = j * 10 + d[i];

			if (sol >= 0 && sol != j)
				return -2;

			sol = j;
		}

		d[pos] = prev;
	}

	return sol;
}

int main()
{
	char s[256];
	int i, j, t;

	while (gets(s) && sscanf(s, "%d", &t) != 1);

	while (t-- > 0) {
		memset(image, ' ', sizeof(image));
		for (i = 0; i < 3; i++) {
			gets(image[i]);
			for (j = 0; j < 32 && image[i][j] != '\0'; j++);
			while (j < 32) image[i][j++] = ' ';
		}

		i = solve();
		if (i == -1)
			printf("failure\n");
		else if (i == -2)
			printf("ambiguous\n");
		else
			printf("%.9d\n", i);
	}

	return 0;
}
