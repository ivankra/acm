/*
ID: infnty1
PROB: camelot
LANG: C++
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <queue>
using namespace std;

#define INF 0x1FFFFFFF

int dx[]={1,1,2,2,-1,-1,-2,-2}, dy[]={2,-2,1,-1,2,-2,1,-1};
int a[64][64], b[64][64], dist[64][64][2], R, C, ky, kx;

int get(int *y, int *x)
{
	char c;
	if (scanf(" %c %d", &c, y) != 2) return 0;
	(*y)--; (*x) = toupper(c) - 'A';
        return 1;
}

int kdist(int y, int x) { return abs(ky-y) >? abs(kx-x); }

struct state { int y, x, k, d; };
bool operator <(const state &a, const state &b) { return a.d > b.d; }

int main()
{
	int i, j, k;
	state s;

	freopen("camelot.in", "r", stdin);
	freopen("camelot.out", "w", stdout);

	scanf("%d %d", &R, &C);
	get(&ky, &kx);

	memset(a, 0, sizeof(a));
	for (i = 0; i < R; i++)
		for (j = 0; j < C; j++)
			b[i][j] = kdist(i,j);

	while (get(&s.y, &s.x)) {
		for (i = 0; i < R; i++)
			for (j = 0; j < C; j++)
				dist[i][j][0] = dist[i][j][1] = INF;

		s.d = s.k = 0;
		dist[s.y][s.x][0] = 0;

		priority_queue<state> q;
		q.push(s);

		while (!q.empty()) {
			s = q.top(); q.pop();
			if (s.d > dist[s.y][s.x][s.k]) continue;

			if (s.k == 0) {
				state t = { s.y, s.x, 1, s.d+kdist(s.y,s.x) };
				if (t.d < dist[t.y][t.x][t.k]) {
					dist[t.y][t.x][t.k] = t.d;
					q.push(t);
				}
			}

			for (i = 0; i < 8; i++) {
				state t = { s.y+dy[i], s.x+dx[i], s.k, s.d+1 };
				if (t.y < 0 || t.x < 0 || t.y >= R || t.x >= C)
					continue;
				if (t.d < dist[t.y][t.x][t.k]) {
					dist[t.y][t.x][t.k] = t.d;
					q.push(t);
				}
			}
		}

		for (i = 0; i < R; i++)
			for (j = 0; j < C; j++) {
				a[i][j] += dist[i][j][0];
				a[i][j] <?= INF;
				if (a[i][j] < INF && dist[i][j][1] < INF)
					b[i][j] <?= dist[i][j][1] - dist[i][j][0];
			}
	}

	for (k = INF, i = 0; i < R; i++)
		for (j = 0; j < C; j++)
			k <?= a[i][j] + b[i][j];
	printf("%d\n", k);

	return 0;
}
