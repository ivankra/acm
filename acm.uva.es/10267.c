#include <stdio.h>
#include <string.h>
#include <assert.h>

char a[256][256];
int width, height;

void fill(char *s)
{
	static int z[262144];
	int i, x, y;
	char c0, c_new;

	i = sscanf(s, "F %d %d %c", &x, &y, &c_new);
	assert(i == 3);

	c0 = a[y][x];
	if (c0 == c_new) return;

	a[y][x] = c_new;

	i = 0;
	z[i++] = y;
	z[i++] = x;

	while (i > 0) {
		x = z[--i];
		y = z[--i];

#define GO(Y,X) if (1 <= (Y) && (Y) <= height && 1 <= (X) && (X) <= width && \
		    a[Y][X] == c0) { \
			a[Y][X] = c_new; \
			z[i++] = Y; \
			z[i++] = X; \
		}

		GO(y - 1, x);
		GO(y + 1, x);
		GO(y, x - 1);
		GO(y, x + 1);

#undef GO
	}
}

void vseg(char *s)
{
	int i, x, y1, y2;
	char c;

	i = sscanf(s, "V %d %d %d %c", &x, &y1, &y2, &c);
	assert(i == 4);

	if (y1 > y2) { i = y1; y1 = y2; y2 = i; }

	for (i = y1; i <= y2; i++)
		a[i][x] = c;
}

void hseg(char *s)
{
	int i, x1, x2, y;
	char c;

	i = sscanf(s, "H %d %d %d %c", &x1, &x2, &y, &c);
	assert(i == 4);

	if (x1 > x2) { i = x1; x1 = x2; x2 = i; }

	for (i = x1; i <= x2; i++)
		a[y][i] = c;
}

void box(char *s)
{
	int i, j, x1, y1, x2, y2;
	char c;

	i = sscanf(s, "K %d %d %d %d %c", &x1, &y1, &x2, &y2, &c);
	assert(i == 5);

	for (i = y1; i <= y2; i++)
		for (j = x1; j <= x2; j++)
			a[i][j] = c;
}

int main()
{
	static char s[65536], c;
	int i, j, x, y;

	memset(a, 0, sizeof(a));
	width = height = -1;

	while (gets(s) && s[0] != 'X') {
		if (s[0] == 'I') {
			sscanf(s, "I %d %d", &width, &height);
			for (i = 1; i <= height; i++)
				for (j = 1; j <= width; j++)
					a[i][j] = 'O';
		} else if (s[0] == 'C') {
			for (i = 1; i <= height; i++)
				for (j = 1; j <= width; j++)
					a[i][j] = 'O';
		} else if (s[0] == 'L') {
			sscanf(s, "L %d %d %c", &x, &y, &c);
			a[y][x] = c;
		} else if (s[0] == 'V') {
			vseg(s);
		} else if (s[0] == 'H') {
			hseg(s);
		} else if (s[0] == 'K') {
			box(s);
		} else if (s[0] == 'F') {
			fill(s);
		} else if (s[0] == 'S') {
			printf("%s\n", (s[1] == '\0') ? "" : (s + 2));
			for (i = 1; i <= height; i++) {
				for (j = 1; j <= width; j++)
					putchar(a[i][j]);
				putchar('\n');
			}
		}
	}

	return 0;
}
