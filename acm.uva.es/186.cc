#include <stdio.h>
#include <string.h>

char cities[128][32], highways[256][32];
int ncities, nways;

int dist[128][128], next[128][128], way[128][128];

void print(int x, int y)
{
	int a;

	printf(
		"From                 To                   Route      Miles\n"
		"-------------------- -------------------- ---------- -----\n"
	);

	for (a = x; a != y; a = next[a][y]) {
		printf("%-20s %-20s %-10s %5d\n",
			cities[a], cities[next[a][y]],
			highways[way[a][next[a][y]]],
			dist[a][next[a][y]]
		);
	}

	printf(
		"                                                     -----\n"
		"                                          Total      %5d\n",
		dist[x][y]
	);
}

int get_c(char *s)
{
	int i;

	for (i = 0; i < ncities; i++)
		if (strcmp(cities[i], s) == 0) return i;

	strcpy(cities[ncities], s);
	return ncities++;
}

int get_w(char *s)
{
	int i;

	for (i = 0; i < nways; i++)
		if (strcmp(highways[i], s) == 0) return i;

	strcpy(highways[nways], s);
	return nways++;
}

int main()
{
	static char buf[655536], s1[1024], s2[1024], s3[1024];
	int i, j, k, x, y, z;

	ncities = 0;
	nways = 0;

	for (i = 0; i < 128; i++) {
		for (j = 0; j < 128; j++) {
			dist[i][j] = 0x3FFFFFFF;
			way[i][j] = -1;
			next[i][j] = j;
		}
		dist[i][i] = 0;
	}

	while (gets(buf)) {
		if (sscanf(buf, "%[^,],%[^,],%[^,],%d", s1, s2, s3, &z) != 4)
			break;

		x = get_c(s1);
		y = get_c(s2);

		if (dist[x][y] <= z)
			continue;

		dist[x][y] = dist[y][x] = z;
		way[x][y] = way[y][x] = get_w(s3);
	}

	for (k = 0; k < ncities; k++) {
		for (i = 0; i < ncities; i++) {
			for (j = i + 1; j < ncities; j++) {
				if ((dist[i][k] + dist[k][j]) >= dist[i][j])
					continue;

				dist[i][j] = dist[i][k] + dist[k][j];
				dist[j][i] = dist[i][j];

				next[i][j] = next[i][k];
				next[j][i] = next[j][k];
			}
		}
	}

	for (k = 0; gets(buf) && sscanf(buf, "%[^,],%[^,]", s1, s2) == 2; k++) {
		x = get_c(s1);
		y = get_c(s2);

		printf("\n\n");
		print(x, y);
	}
//	printf("\n\n");

	return 0;
}
