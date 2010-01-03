#include <stdio.h>
#include <string.h>

int main()
{
	static char a[40][128];
	static int sx[4096], sy[4096], sc[4096], sp;
	int i, j, c, m, cont;

	for (;;) {
		memset(a, 0, sizeof(a));

		for (m = 1; gets(a[m] + 1) && a[m][1] != '_'; m++);

		if (a[m][1] == '\0')
			break;

		for (i = 1, cont = 0; cont == 0 && i <= m; i++)
			for (j = 1; a[i][j]; j++)
				if (a[i][j] != ' ') {
					cont = a[i][j];
					break;
				}

		if (cont == 0 || cont == '_')
			break;

		for (sp = 0, i = 1; i <= m; i++)
			for (j = 1; a[i][j]; j++)
				if (a[i][j] != '_' && a[i][j] != ' ' &&
				    a[i][j] != cont) {
					sy[sp] = i;
					sx[sp] = j;
					sc[sp] = a[i][j];
					sp++;
				}

		while (sp-- > 0) {
			i = sy[sp];
			j = sx[sp];
			c = sc[sp];

#define GO(y,x) if (a[y][x] && a[y][x] != cont && a[y][x] != c)\
	         { sy[sp] = (y); sx[sp] = (x); sc[sp++] = c; a[y][x] = c; }
				
			GO(i - 1, j);
			GO(i, j - 1);
			GO(i, j + 1);
			GO(i + 1, j);
		}

		for (i = 1; i <= m; i++) {
			for (j = 1; a[i][j]; j++)
				putchar(a[i][j]);
			putchar('\n');
		}
	}

	return 0;
}
