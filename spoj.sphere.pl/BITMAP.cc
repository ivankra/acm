#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <queue>
using namespace std;

char bmp[256][256];
int dist[256][256], N, M;

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &N, &M) == 2; cs++) {
		for (int i = 0; i < N; i++) scanf(" %s", bmp[i]);
		queue<int> q;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (bmp[i][j] == '1') {
					dist[i][j] = 0;
					q.push(i*256+j);
				} else {
					dist[i][j] = 1<<30;
				}
			}
		}

		while (!q.empty()) {
			int y0 = q.front() >> 8;
			int x0 = q.front() & 255;
			for (int i = 0; i < 4; i++) {
				int y = y0 + "1102"[i] - '1';
				int x = x0 + "0211"[i] - '1';
				if (0 <= y && y < N && 0 <= x && x < M && dist[y][x] > dist[y0][x0] + 1) {
					dist[y][x] = dist[y0][x0] + 1;
					q.push(y*256+x);
				}
			}
			q.pop();
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				printf("%d ", dist[i][j]);
			}
			printf("\n");
		}
	}
}
