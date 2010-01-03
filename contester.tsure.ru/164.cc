#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

char Map[64][64];
int width, height, seen[64*64], heap[64*64], loc[64*64], N;
double diag = sqrt(2.0), dist[64*64];

int cell(int ys, int xs) { return ys * 64 + xs; }

void up(int k) {
	int t = heap[k];
	for (; k > 1 && dist[heap[k/2]] > dist[t]; k /= 2)
		loc[heap[k] = heap[k/2]] = k;
	loc[heap[k] = t] = k;
}

void down(int k) {
	for (;;) {
		int i = 2 * k;
		if (i > N) break;

		if (i+1 < N && dist[heap[i+1]] < dist[heap[i]]) i++;

		if (dist[heap[k]] > dist[heap[i]]) {
			int t = heap[k];
			loc[heap[k] = heap[i]] = k;
			loc[heap[i] = t] = i;
			k = i;
		} else {
			break;
		}
	}
}

double Distance(int xs, int ys, int xt, int yt) {
	memset(seen, 0, sizeof(seen));
	for (int i = 0; i < 64*64; i++) {
		dist[i] = 1e99;
		loc[i] = 0;
	}
        dist[cell(ys, xs)] = 0;

	loc[heap[1] = cell(ys, xs)] = 1;
        N = 1;

        while (N > 0) {
        	int c = heap[1];

        	if (--N > 0) {
	        	loc[heap[1] = heap[N+1]] = 1;
	        	down(1);
		}

        	int y0 = c/64, x0 = c%64;
        	if (y0 == yt && x0 == xt) return dist[c];

        	seen[c] = 1;

		for (int dy = -1; dy <= 1; dy++) {
			for (int dx = -1; dx <= 1; dx++) {
	        		int y = y0 + dy, x = x0 + dx;
        			if (x < 1 || x > width) continue;
        			if (y < 1 || y > height) continue;
        			if (Map[y][x] == '#') continue;

        			int d = cell(y, x);
        			if (seen[d]) continue;

        			double m = dist[c];
        			m += (dx != 0 && dy != 0 ? diag : 1.0);
        			if (dist[d] < m+1e-6) continue;
        			dist[d] = m;

        			if (loc[d] == 0) {
        				N++;
        				loc[heap[N] = d] = N;
				}

				up(loc[d]);
			}
        	}
        }

        return -1;
}

int main() {
	int K;
	double V;
	assert(scanf("%d %d %d %lf", &width, &height, &K, &V) == 4);

	memset(Map, '#', sizeof(Map));
	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			assert(scanf(" %c", &Map[i][j]) == 1);
			assert(Map[i][j] == '.' || Map[i][j] == '#');
		}
	}

	int x, y;
	assert(scanf("%d %d", &x, &y) == 2);
	assert(1 <= x && x <= width && 1 <= y && y <= height);
	assert(Map[y][x] != '#');

	double res = 0;

	for (int i = 0; i < K; i++) {
		int x1, y1;
		assert(scanf("%d %d", &x1, &y1) == 2);
		if (x1 < 1 || x1 > width || y1 < 1 || y1 > height) continue;

		double t = Distance(x, y, x1, y1);
//printf("distance from (y=%d x=%d) to (y=%d x=%d) = %.5f\n",y,x,y1,x1,t);
		if (t >= 0.0) {
			res += t;
			x = x1;
			y = y1;
		}
	}
	printf("%.2f\n", res/V);
	return 0;
}
