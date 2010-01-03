#include <stdio.h>
#include <memory.h>

int main()
{
	static char text[16][16], buf[4096];
	static int t, n, mode, row, col;
	register int i;
	register char *p;

	for (t = 1; scanf("%d\n", &n) == 1 && n > 0; t++) {
		memset(text, ' ', sizeof(text));
		mode = row = col = 0;

		while (n-- > 0 && gets(buf)) {
			for (p = buf; *p;) {
				if (p[0] != '^' || p[1]=='\0' ||
				    (p[0] == '^' && p[1] == '^')) {
					if (p[0] == '^' && p[1] == '^')
						p++;

					if (mode == 0) {
						text[row][col] = *p++;
						if (col < 9) col++;
					} else {
						for (i = 9; i > col; i--)
						   text[row][i]=text[row][i-1];
						text[row][col] = *p++;
						if (col < 9) col++;
					}

					continue;
				}

				p++;
				switch (*p++) {
				case 'b':
					col = 0;
					break;
				case 'c':
					memset(text, ' ', sizeof(text));
					break;
				case 'd':
					if (row < 9) row++;
					break;
				case 'e':
					for (i = col; i < 10; i++)
						text[row][i] = ' ';
					break;
				case 'h':
					row = col = 0;
					break;
				case 'i':
					mode = 1;
					break;
				case 'l':
					if (col > 0) col--;
					break;
				case 'o':
					mode = 0;
					break;
				case 'r':
					if (col < 9) col++;
					break;
				case 'u':
					if (row > 0) row--;
					break;
				default:
					p--;
					if ((p[0] >= '0' && p[0] <= '9') &&
					    (p[1] >= '0' && p[1] <= '9')) {
						row = p[0] - '0';
						col = p[1] - '0';
						p += 2;
						break;
					}

					p++;
					break;
				}
			}
		}		

		printf("Case %d\n+----------+\n", t);
		for (i = 0; i < 10; i++)
			printf("|%.10s|\n", text[i]);
		printf("+----------+\n");
	}

	return 0;
}
