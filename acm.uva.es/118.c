#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
	static int map[64][64], left[256], right[256], dx[256], dy[256];
	int x, y, nx, ny, mx, my, dir;
	char s1[256], s2[256], *p;

	gets(s1);
	sscanf(s1, "%d %d", &mx, &my);
	memset(map, 0, sizeof(map));

	left['N'] = 'W';
	left['W'] = 'S';
	left['S'] = 'E';
	left['E'] = 'N';

	right['N'] = 'E';
	right['E'] = 'S';
	right['S'] = 'W';
	right['W'] = 'N';

	dx['N'] = 0; dy['N'] = 1;
	dx['S'] = 0; dy['S'] = -1;
	dx['W'] = -1; dy['W'] = 0;
	dx['E'] = 1; dy['E'] = 0;

	while (gets(s1)) {
		if (sscanf(s1, "%d %d %s", &x, &y, s2) != 3)
			continue;

		dir = toupper(s2[0]);
		gets(s1);

		for (p = s1;; p++) {
			if (*p == '\0') {
				printf("%d %d %c\n", x, y, dir);
				break;
			}

			if (*p == 'L' || *p == 'l')
				dir = left[dir];
			else if (*p == 'R' || *p == 'r')
				dir = right[dir];

			if (*p != 'F' && *p != 'f')
				continue;

			nx = x + dx[dir];
			ny = y + dy[dir];

			if (0 <= nx && nx <= mx && 0 <= ny && ny <= my) {
				x = nx;
				y = ny;
				continue;
			}

			if (map[x][y])
				continue;

			map[x][y] = 1;
			printf("%d %d %c LOST\n", x, y, dir);
			break;
		}
	}

	return 0;
}
