#include <stdio.h>
#include <string.h>

#define	INF	0x3FFFFFFF
#define	DIM	32
#define WALL	1
#define	GOAL	2
#define	BOX	4

#define HSIZE	700000
#define	HDIV	131071

struct {
	unsigned a[9], m, next;
} hdata[HSIZE];

int map[DIM][DIM], ndist[DIM][DIM], dead1[DIM][DIM];
int minx, maxx, miny, maxy, height, width, bsize, many, manx, maxlen;
int htab[HDIV], hsize;

int hcheck(unsigned p, int m)
{
	static unsigned a[9];
	int i, j, k, h;

	for (i = 0; i < 9; i++)
		a[i] = 0;

	for (h = 0, i = miny; i <= maxy; i++) {
		for (j = minx; j <= maxx; j++) {
			if ((map[i][j] & BOX) == 0) continue;
			k = (i - miny) * width + j - minx;
			a[k >> 5] |= 1U << (k & 31);

			h = h * bsize + k;
			if (h >= HDIV) h %= HDIV;
		}
	}
	a[8] = p;

	for (i = htab[h]; i != 0; i = hdata[i].next) {
		if (memcmp(hdata[i].a, a, 9 * sizeof(unsigned)) == 0) {
			if (m >= hdata[i].m) return 1;
			hdata[i].m = m;
			return 0;
		}
	}

	if ((hsize + 1) >= HSIZE)
		return 0;

	i = ++hsize;
	hdata[i].next = htab[h];
	hdata[i].m = m;
	htab[h] = i;
	for (j = 0; j < 9; j++)
		hdata[i].a[j] = a[j];

	return 0;
}

int estimate()
{
	int i, j, r;

	for (r = 0, i = miny; i <= maxy; i++) {
		for (j = minx; j <= maxx; j++) {
			if ((map[i][j] & BOX) == 0) continue;
			if (dead1[i][j]) return INF;
			r += ndist[i][j];
		}
	}

	return r;
}

void fill(int a[DIM][DIM], int y, int x)
{
	static int s[DIM * DIM * 2];
	int t;

	a[s[0] = y][s[1] = x] = 1;
	for (t = 2; t > 0;) {
		x = s[--t];
		y = s[--t];

#define GO(Y,X) if (a[Y][X] == 0 && (map[Y][X] & (WALL | BOX)) == 0) \
		 { a[Y][X] = 1; s[t++] = Y; s[t++] = X; }
		GO(y + 1, x);
		GO(y - 1, x);
		GO(y, x + 1);
		GO(y, x - 1);
#undef GO
	}
}

int find(int m, int y0, int x0)
{
	static int a[32][DIM][DIM];
	int y, x;

	if (hcheck((y0 << 8) | x0, m))
		return 0;

	x = estimate(map);
	if (x == 0)
		return 1;

	if ((m + x) > maxlen)
		return 0;

	for (y = miny; y <= maxy; y++)
		for (x = minx; x <= maxx; x++)
			a[m][y][x] = 0;

	fill(a[m], y0, x0);

	for (y = miny; y <= maxy; y++) {
		for (x = minx; x <= maxx; x++) {

			if (a[m][y][x] == 0)
				continue;

#define PUSH(dy,dx) \
	if ((map[y + dy][x + dx] & BOX) && \
	    (map[y + dy + dy][x + dx + dx] & (BOX | WALL)) == 0) { \
		map[y + dy][x + dx] ^= BOX; \
		map[y + dy + dy][x + dx + dx] ^= BOX; \
		if (find(m + 1, y + dy, x + dx)) return 1; \
		map[y + dy][x + dx] ^= BOX; \
		map[y + dy + dy][x + dx + dx] ^= BOX; \
	}
			PUSH(1, 0);
			PUSH(-1, 0);
			PUSH(0, 1);
			PUSH(0, -1);
#undef PUSH
		}
	}

	return 0;
}

int get_ndist(int y, int x)
{
	static int d[DIM][DIM], q[DIM * DIM * 2];
	int i, h, t, y1, x1;

	if (map[y][x] & WALL)
		return 0;

	memset(d, 0, sizeof(d));
	h = t = 0;
	q[t++] = y;
	q[t++] = x;
	d[y][x] = 1;

	while (h < t) {
		y = q[h++];
		x = q[h++];
		if (map[y][x] & GOAL)
			return (d[y][x] - 1);

		for (i = 0; i < 4; i++) {
			y1 = y + "0211"[i] - '1';
			x1 = x + "1102"[i] - '1';
			if ((map[y1][x1] & WALL) == 0 && d[y1][x1] == 0) {
				d[y1][x1] = d[y][x] + 1;
				q[t++] = y1;
				q[t++] = x1;
			}
		}
	}

	return 0;
}

int prepmap()
{
	static int v[DIM][DIM], s[DIM * DIM * 2];
	int i, j, k, y, x, y1, x1;

	memset(v, 0, sizeof(v));
	k = 0;
	s[k++] = many;
	s[k++] = manx;
	v[many][manx] = 1;

	while (k > 0) {
		x = s[--k];
		y = s[--k];

		for (i = 0; i < 4; i++) {
			y1 = y + "0211"[i] - '1';
			x1 = x + "1102"[i] - '1';
			if ((map[y1][x1] & WALL) == 0 && v[y1][x1] == 0) {
				v[y1][x1] = 1;
				s[k++] = y1;
				s[k++] = x1;
			}
		}
	}

	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			if (v[i][j]) continue;
			if (map[i][j] & (BOX | GOAL)) return 1;
			map[i][j] = WALL;
		}
	}

	for (k = 0, i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			if (map[i][j] == WALL) continue;

			if (k++ == 0) {
				miny = maxy = i;
				minx = maxx = j;
				continue;
			}

			if (i < miny) miny = i;
			if (i > maxy) maxy = i;
			if (j < minx) minx = j;
			if (j > maxx) maxx = j;
		}
	}

	for (k = 0, i = miny; i <= maxy; i++)
		for (j = minx; j <= maxx; j++)
			k += ((map[i][j] & BOX) ? 1 : 0) + ((map[i][j] & GOAL) ? -1 : 0);

	if (k != 0)
		return 1;

	width = maxx - minx + 1;
	height = maxy - miny + 1;
	bsize = width * height;

	memset(ndist, 0, sizeof(ndist));
	for (i = miny; i <= maxy; i++)
		for (j = minx; j <= maxx; j++)
			ndist[i][j] = get_ndist(i, j);

	memset(dead1, 0, sizeof(dead1));
	for (i = miny; i <= maxy; i++) {
		for (j = minx; j <= maxx; j++) {
			if (map[i][j] & GOAL) continue;

			if (map[i + 1][j] & map[i][j + 1] & WALL)
				dead1[i][j] = 1;

			if (map[i - 1][j] & map[i][j + 1] & WALL)
				dead1[i][j] = 1;

			if (map[i + 1][j] & map[i][j - 1] & WALL)
				dead1[i][j] = 1;

			if (map[i - 1][j] & map[i][j - 1] & WALL)
				dead1[i][j] = 1;
		}
	}

	return 0;
}

int main()
{
	char s[1024];
	int i, j, k;

	while (gets(s)) {
		if (sscanf(s, "%d", &maxlen) != 1)
			continue;

		for (i = 0; i < DIM; i++)
			for (j = 0; j < DIM; j++)
				map[i][j] = WALL;

		for (i = 1; gets(s) && s[0] != '\0' && s[0] != '\r'; i++) {
			for (j = 1, k = 0; s[k]; j++, k++) {
				switch (s[k]) {
				  case ' ': map[i][j] = 0; break;
				  case '#': map[i][j] = WALL; break;
				  case '.': map[i][j] = GOAL; break;
				  case '$': map[i][j] = BOX; break;
				  case '*': map[i][j] = BOX | GOAL; break;
				  case '@': map[i][j] = 0; many = i; manx = j; break;
				  case '+': map[i][j] = GOAL; many = i; manx = j; break;
				}
			}
		}

		if (prepmap()) {
			printf("NO\n");
			continue;
		}

		memset(htab, 0, sizeof(htab));
		hsize = 0;

		printf(find(0, many, manx) ? "YES\n" : "NO\n");
	}

	return 0;
}
