#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct { int a[11][10], ne, sy, sx; } map;

int dx[] = { -1, -1, -1, 1, 1, 1, 0, 0, 0 };
int dy[] = { -1, 0, 1, -1, 0, 1, -1, 1, 0 };
int C[16][16][16][16];

void prep()
{
	int x0, y0, x1, y1, x2, y2, c, d, q;

	for(y0=1;y0<=9;y0++) for(x0=1;x0<=8;x0++)
		for(y1=1;y1<=9;y1++) for(x1=1;x1<=8;x1++) {
			for (c = 0, q = 0x7fffffff; c < 8; c++) {
				y2 = y1 + dy[c];
				x2 = x1 + dx[c];
				d = (y2-y0)*(y2-y0)+(x2-x0)*(x2-x0);
				if (d < q) q=d, C[y0][x0][y1][x1]=c;
			}
		}
}

int solve(map *u, int m)
{
	int i, j, k, d;
	map v;

/*printf("map:  m=%d ne=%d\n",m,u->ne);
for(i=0;i<=10;i++){for(j=0;j<=9;j++)if(i==u->sy&&j==u->sx)putchar('S');else putchar(u->a[i][j]?u->a[i][j]:'.');
putchar('\n');}*/

	if (u->ne == 0) return 1;
	if (m == 0) return 0;

	for (d = 0; d < 8; d++) {
		if (u->a[u->sy+dy[d]][u->sx+dx[d]]) continue;

		for (i = 0; i <= 10; i++)
			for (j = 0; j <= 9; j++)
				v.a[i][j] = (u->a[i][j] == 'E') ? 0 : u->a[i][j];
		v.sy = u->sy + dy[d];
		v.sx = u->sx + dx[d];
		v.ne = 0;

		for (i = 1; i <= 9; i++) {
			for (j = 1; j <= 8; j++) {
				if (u->a[i][j] != 'E') continue;
				k = C[v.sy][v.sx][i][j];
				if ((i+dy[k]) == v.sy && (j+dx[k]) == v.sx) goto skip;
				if (v.a[i+dy[k]][j+dx[k]] != 0) {
					if (v.a[i+dy[k]][j+dx[k]] == 'E')
						v.a[i+dy[k]][j+dx[k]] = 1, v.ne--;
					continue;
				}
				v.a[i+dy[k]][j+dx[k]] = 'E'; v.ne++;
			}
		}

		if (solve(&v, m-1)) return 1;
skip:;
	}

	return 0;
}

int main()
{
	int i, j, c, t;
	map m;

	prep();

	for (scanf("%d", &t); t-- > 0;) {
		memset(&m, 0, sizeof(m));
		for (i = 0; i <= 10; i++)
			m.a[0][i] = m.a[10][i] = 1;
		for (i = 0; i <= 9; i++)
			m.a[i][0] = m.a[i][9] = 1;

		for (i = 1; i <= 9; i++) {
			for (j = 1; j <= 8 && (c = getchar()) != EOF; c++) {
				c = toupper(c);
				if (c == 'S')
					m.sy = i, m.sx = j, j++;
				else if (c == '.')
					j++;
				else if (c == '#')
					m.a[i][j++] = 1;
				else if (c == 'E')
					m.a[i][j++] = 'E', m.ne++;
			}
		}

		if (solve(&m, 9))
			printf("I'm the king of the Seven Seas!\n");
		else
			printf("Oh no! I'm a dead man!\n");
	}

	return 0;
}
