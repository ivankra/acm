#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* tab[A][y][x] = f((y,x), A) in my explanation
   map[1..height][1..width] = the input map

   Sets of people are represented as combinations of 1=A, 2=B, 4=C, 8=D.

   The dynamic programming is run for all subsets of {A,B,C}.
   The minimum-cost solution is then given by tracing f(<location of D>, {A,B,C}).
 */

#define INF 0x3FFFFFFF

int tab[8][32][32], map[32][32], width, height;
int dtab[8][32][32], btab[8][32][32];    /* auxiliary info to reconstruct the solution */

#define VERT(y,x) (((y)<<5) | (x))
#define VERT2Y(v) ((v) >> 5)
#define VERT2X(v) ((v) & 31)
int heap[1024], heaploc[1024], dist[1024], heapn;

void heap_up(int p)
{
	int v = heap[p];
	for (; p > 1 && dist[heap[p>>1]] > dist[v]; p >>= 1)
		heaploc[heap[p] = heap[p>>1]] = p;
	heaploc[heap[p] = v] = p;
}

void heap_down(int p)
{
	int q, r;
	for (; (q=2*p) <= heapn; p = r) {
		r = (dist[heap[q]] < dist[heap[p]]) ? q : p;
		if (++q <= heapn && dist[heap[q]] < dist[heap[r]]) r = q;
		if (p == r) break;
		q = heap[p];
		heaploc[heap[p] = heap[r]] = p;
		heaploc[heap[r] = q] = r;
	}
	heaploc[heap[p]] = p;
}

int dy[]={-1,0,1,0}, dx[]={0,1,0,-1};  /* NESW */

/* Computes all tab[A][y][x] for a given A.
   Assumes that all tab[B][y][x] have already been computed for all
   proper subsets B of A. */
void make(int A)
{
	int x, y, u, v, d, t, B;

	if (A == 0) {
		for (y = 0; y <= height+1; y++)
			for (x = 0; x <= width+1; x++)
				if (map[y][x] == '#')
					tab[0][y][x] = INF;
				else if (map[y][x] == 'o')
					tab[0][y][x] = 1;
				else
					tab[0][y][x] = 0;
		return;
	}

	for (y = 1; y <= height; y++) {
		for (x = 1; x <= width; x++) {
			tab[A][y][x] = INF;

			if (isupper(map[y][x]) && (A & (1<<(map[y][x]-'A'))) != 0) {
				tab[A][y][x] = tab[A ^ (1<<(map[y][x]-'A'))][y][x];
				continue;
			}

			if (map[y][x] == '#') continue;

			for (B = 1; B < A; B++) {
				if ((A & B) != B) continue;
				/* for all proper subsets B of A... */

				for (d = 0; d < 4; d++) {
					if (map[y+dy[d]][x+dx[d]] == '#')
						continue;

					t = tab[A^B][y][x] + tab[B][y+dy[d]][x+dx[d]];
					if (t >= tab[A][y][x]) continue;

					tab[A][y][x] = t;
					dtab[A][y][x] = d;
					btab[A][y][x] = B;
				}
			}
		}
	}

	/* dijkstra part starts */

	heapn = 0;
	for (y = 1; y <= height; y++) {
		for (x = 1; x <= width; x++) {
			u = VERT(y, x);
			dist[u] = tab[A][y][x];
			if (dist[u] < INF) {
				heap[++heapn] = u;
				heap_up(heapn);
			}
		}
	}

	while (heapn > 0) {
		v = heap[1];
		if (--heapn > 0) { heap[1] = heap[heapn+1]; heap_down(1); }

		y = VERT2Y(v);
		x = VERT2X(v);

		tab[A][y][x] = dist[v];

		for (d = 0; d < 4; d++) {
/*f(u,A) = min_v f(v,A) + f(u,0).*/

			t = dist[v] + tab[0][y+dy[d]][x+dx[d]];
			u = VERT(y+dy[d],x+dx[d]);
			if (t >= dist[u]) continue;

			dtab[A][y+dy[d]][x+dx[d]] = (d + 2) & 3;  /*opposite dir.*/
			btab[A][y+dy[d]][x+dx[d]] = A;

			if (dist[u] == INF) {
				heapn++;
				heaploc[heap[heapn] = u] = heapn;
			}

			dist[u] = t;
			heap_up(heaploc[u]);
		}
	}
}

/* Reconstructs the solution -- traces the choices of B,d made during DP, and updates the map correspondingly. */
void update(int A, int y, int x)
{
	int i;

	if (map[y][x] == 'o') map[y][x] = '.';
	if (isupper(map[y][x])) A &= ~(1 << (map[y][x] - 'A'));
	if (A == 0) return;

	i = dtab[A][y][x];
	update(btab[A][y][x], y+dy[i], x+dx[i]);
	update(A ^ btab[A][y][x], y, x);
}

int main()
{
	int s[] = { 0, 1, 2, 4, 1+2, 1+4, 2+4, 1+2+4, -1 };
	int i, j, k;

	while (scanf("%d %d", &width, &height) == 2 && width > 0) {
		for(i=0;i<32;i++) for(j=0;j<32;j++) map[i][j] = '#';

		for (i = 1; i <= height; i++)
			for (j = 1; j <= width && (k = getchar()) != EOF;)
				if (strchr("#.oABCD", k) != NULL) map[i][j++] = k;

		for (i = 0; s[i] >= 0; i++)
			make(s[i]);

		for (i = j = 1; i <= height; i++) {
			for (j = 1; j <= width && map[i][j] != 'D'; j++);
			if (j <= width) break;
		}

		if (i <= height && tab[7][i][j] < INF)
			update(7,i,j);

		printf("%d %d\n", width, height);
		for (i = 1; i <= height; i++) {
			for (j = 1; j <= width; j++) putchar(map[i][j]);
			putchar('\n');
		}
		printf("\n");
	}
	printf("0 0\n");
	return 0;
}
