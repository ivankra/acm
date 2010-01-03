#include <stdio.h>
#include <string.h>

int heap[524288], heap_n;
int dist[524288], rank[524288], pred[524288], action[524288];

int cpick[32], ccarry[32], cmove, nrows, ncols, ntreas;
int start_r, start_c, end_r, end_c, start_st, end_st, full_treas;
int map_wall[32][32], map_treas[32][32];

void heap_up(int p)
{
	int z;

	for (z = heap[p]; p > 1 && dist[heap[p >> 1]] > dist[z]; p >>= 1)
		rank[heap[p] = heap[p >> 1]] = p;

	heap[p] = z;
	rank[z] = p;
}

void heap_down(int p)
{
	int i, t;

	while ((p << 1) <= heap_n) {
		i = (dist[heap[p << 1]] < dist[heap[p]]) ? (p << 1) : p;

		if (((p << 1) | 1) <= heap_n &&
		    dist[heap[(p << 1) | 1]] < dist[heap[i]])
			i = (p << 1) | 1;

		if (i == p)
			break;

		t = heap[p];
		rank[heap[p] = heap[i]] = p;
		rank[heap[p = i] = t] = i;
	}
}

void heap_add(int x, int k)
{
	heap_n++;
	heap[heap_n] = x;
	dist[x] = k;
	rank[x] = heap_n;
	heap_up(heap_n);
}

int heap_get()
{
	int r;

	if (heap_n <= 0)
		return -1;

	rank[r = heap[1]] = -1;
	heap_n--;

	if (heap_n > 0) {
		rank[heap[1] = heap[heap_n + 1]] = 1;
		heap_down(1);
	}

	return r;
}

int encode(int y, int x, int m)
{
	return ((y * ncols + x) << ntreas) | m;
}

void add(int st, int p, int a, int d)
{
	if (rank[st] < 0)
		return;

	if (rank[st] == 0) {
		pred[st] = p;
		action[st] = a;
		heap_add(st, d);
	} else if (dist[st] > d) {
		dist[st] = d;
		pred[st] = p;
		action[st] = a;
		heap_up(rank[st]);
	}
}

void solve()
{
	static int dx[] = { 1, 0, -1, 0 }, dy[] = { 0, 1, 0, -1 };
	static int da[] = { 'E', 'S', 'W', 'N' };
	static int path[65536];
	int i, j, k, y, x, m, st;

	memset(map_wall, 0, sizeof(map_wall));
	for (i = 0, ntreas = 0; i < nrows; i++) {
		for (j = 0; j < ncols && (k = getchar()) != EOF;) {
			map_treas[i][j] = -1;
			if (k == 'S') {
				start_r = i;
				start_c = j++;
			} else if (k == 'T') {
				end_r = i;
				end_c = j++;
			} else if (k == '*') {
				map_treas[i][j++] = ntreas++;
			} else if (k == '#') {
				map_wall[i][j++] = 1;
			} else if (k == '.') {
				j++;
			}
		}
	}

	full_treas = (1 << ntreas) - 1;

	scanf("%d", &cmove);
	for (i = 0; i < ntreas; i++)
		scanf("%d %d", &cpick[i], &ccarry[i]);

	memset(rank, 0, sizeof(rank));

	start_st = encode(start_r, start_c, 0);
	end_st = encode(end_r, end_c, full_treas);

	heap_n = 0;
	heap_add(start_st, 0);

	while ((st = heap_get()) >= 0 && st != end_st) {
		y = (st >> ntreas) / ncols;
		x = (st >> ntreas) % ncols;
		m = st & full_treas;

		i = map_treas[y][x];
		if (i >= 0 && ((m >> i) & 1) == 0)
			add(encode(y, x, m | (1 << i)), st, 'P', dist[st] + cpick[i]);

		for (k = cmove, i = 0; i < ntreas; i++)
			if (((m >> i) & 1) == 1) k += ccarry[i];

		for (i = 0; i < 4; i++) {
			if ((x + dx[i]) < 0 || (x + dx[i]) >= ncols) continue;
			if ((y + dy[i]) < 0 || (y + dy[i]) >= nrows) continue;
			if (map_wall[y + dy[i]][x + dx[i]]) continue;
			add(encode(y + dy[i], x + dx[i], m), st, da[i], dist[st] + k);
		}
	}

	if (st != end_st) {
		printf("The hunt is impossible.\n\n");
		return;
	}

	printf("Minimum energy required = %d cal\n", dist[st]);

	for (i = 0, k = st; k != start_st; k = pred[k])
		path[i++] = action[k];

	while (i-- > 0)
		putchar(path[i]);
	printf("\n\n");
}

int main()
{
	int t;

	for (t = 1; scanf("%d %d", &nrows, &ncols) == 2 && nrows > 0; t++) {
		printf("Hunt #%d\n", t);
		solve();
	}

	return 0;
}
