#include <stdio.h>
#include <string.h>

int walls[32][32], place_r[32], place_c[32], nrows, ncols, reachable;
int dist[32][32], n;
char path[32][32][256];

void bfs(int u, int v)
{
	static int dr[] = { 0, -1, 1, 0 }, dc[] = { 1, 0, 0, -1 };
	static int q[2048], d[32][32], h, t;
	int i, k, r, c, r1, c1;

	memset(d, 0, sizeof(d));
	h = t = 0;
	q[t++] = place_r[v];
	q[t++] = place_c[v];
	d[place_r[v]][place_c[v]] = 1;

	while (h < t) {
		r = q[h++];
		c = q[h++];

		for (i = 0; i < 4; i++) {
			r1 = r + dr[i];
			c1 = c + dc[i];

			if (0 <= r1 && r1 < nrows && 0 <= c1 && c1 < ncols &&
			    walls[r1][c1] == 0 && d[r1][c1] == 0) {
				d[r1][c1] = d[r][c] + 1;
				q[t++] = r1;
				q[t++] = c1;
			}
		}
	}

	if (d[place_r[u]][place_c[u]] == 0 || d[place_r[u]][place_c[u]] > 205) {
		dist[u][v] = -1;
		strcpy(path[u][v], "?");
		return;
	}

	for (k = 0, r = place_r[u], c = place_c[u]; d[r][c] > 1;) {
		for (i = 0; i < 4; i++) {
			r1 = r + dr[i];
			c1 = c + dc[i];
			if (0 <= r1 && r1 < nrows && 0 <= c1 && c1 < ncols &&
			    d[r1][c1] == (d[r][c] - 1))
				break;
		}
		path[u][v][k++] = "ENSW"[i];
		r = r1;
		c = c1;
	}
	path[u][v][k] = '\0';

	dist[u][v] = strlen(path[u][v]);
}

int tab_len[32][2048], tab_next[32][2048];

int search(int s, int m)
{
	int t, r, y, z;

	if (tab_len[s][m] >= 0)
		return tab_len[s][m];

	if (s == 0 && m == reachable) {
		tab_next[s][m] = 0;
		return (tab_len[s][m] = 0);
	}

	for (r = y = -1, z = 0; z < n; z++) {
		if (((m >> z) & 1) || dist[s][z] < 0)
			continue;

		t = dist[s][z] + search(z, m | (1 << z));

		if (r < 0 || t < r || (r == t && strcmp(path[s][z], path[s][y]) < 0)) {
			r = t;
			y = z;
		}
	}

	if (r < 0)
		r = dist[s][y = 0];

	tab_next[s][m] = y;
	return (tab_len[s][m] = r);
}

int main()
{
	int i, j, c;

	while (scanf("%d %d", &nrows, &ncols) == 2 && nrows > 0) {
		memset(walls, 0, sizeof(walls));
		for (n = 1, i = 0; i < nrows; i++) {
			for (j = 0; j < ncols && (c = getchar()) != EOF;) {
				if (c == '#' || c == 'X') {
					walls[i][j++] = 1;
				} else if (c == 'S') {
					place_r[0] = i;
					place_c[0] = j++;
				} else if (c == '*') {
					place_r[n] = i;
					place_c[n++] = j++;
				} else if (c == ' ') {
					j++;	
				}
			}
		}

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				bfs(i, j);

		for (reachable = 0, i = 0; i < n; i++)
			if (dist[0][i] >= 0) reachable |= (1 << i);

		for (i = 0, c = (1 << n); i < n; i++)
			for (j = 0; j < c; j++)
				tab_len[i][j] = -1;

		if ((c = search(0, 0)) == 0) {
			printf("Stay home!\n");
			continue;
		}

		for (i = 0, j = 0; i != 0 || j != reachable;) {
			printf("%s", path[i][tab_next[i][j]]);
			j |= (1 << (i = tab_next[i][j]));
		}
		printf("\n");
	}

	return 0;
}
