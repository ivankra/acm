#include <cstdio>
#include <cctype>
#include <cassert>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

struct Wall {
	int x1, y1, x2, y2, len;
	// x1<=x2 y1<=y2

	bool in(int x, int y) {
		if (x1 == x2)
			return x==x1 && y1<=y && y<=y2;
		else //y1==y2
			return y==y1 && x1<=x && x<=x2;
	}
};

bool by_len(const Wall &a, const Wall &b) { return a.len < b.len; }

Wall walls[512];
int block[8][8][8][8], block_id, N, pathlen;
char isect[512][512], path[1024];

int c2dx[256], c2dy[256];

int main() {
	memset(c2dx, 0, sizeof(c2dx));
	memset(c2dy, 0, sizeof(c2dy));
	c2dy['N'] = -1; c2dx['N'] = 0;
	c2dy['S'] = 1; c2dx['S'] = 0;
	c2dy['W'] = 0; c2dx['W'] = -1;
	c2dy['E'] = 0; c2dx['E'] = 1;

	int len[3], len_orig[3];
	while (scanf("%d %d %d %s", &len[0], &len[1], &len[2], path) == 4) {
		if (len[0] == 0 && len[1] == 0 && len[2] == 0) break;
		assert(len[0] >= 1 && len[1] >= 1 && len[2] >= 1);
		assert(len[0] <= 6 && len[1] <= 6 && len[2] <= 6);

		for (int i = 0; i < 3; i++) len_orig[i] = len[i];

		sort(len, len+3);

		for (int i = 0; path[i]; i++) {
			path[i] = toupper(path[i]);
			assert(strchr("NWES", path[i]) != NULL);
		}
		pathlen = strlen(path);

// --- Generate walls
		N = 0;
		Wall w;
		for (w.x1 = 0; w.x1 <= 6; w.x1++)
		for (w.y1 = 0; w.y1 <= 6; w.y1++)
		for (w.x2 = 0; w.x2 <= 6; w.x2++)
		for (w.y2 = 0; w.y2 <= 6; w.y2++) {
			if (w.x1 == w.x2) w.len = w.y2 - w.y1;
			else if (w.y1 == w.y2) w.len = w.x2 - w.x1;
			else continue;

			if (w.len <= 0) continue;
			if (w.len != len[0] && w.len != len[1] && w.len != len[2]) continue;

			if (w.y1==0 && w.y2==0 && w.x1 != 0) continue;
			if (w.y1==6 && w.y2==6 && w.x1 != 0) continue;

			if (w.x1==0 && w.x2==0 && w.y1 != 0) continue;
			if (w.x1==6 && w.x2==6 && w.y1 != 0) continue;

			assert(N <= 510);
			walls[N++] = w;
		}

		sort(walls, walls+N, by_len);

// --- Determine intersecting walls
		memset(isect, 0, sizeof(isect));
		for (int i = 0; i < N; i++) {
			isect[i][i] = 1;
			for (int j = i+1; j < N; j++) {
				Wall &u = walls[i], &v = walls[j];

				int c = 0;
				for (int x = 0; x <= 6; x++)
				for (int y = 0; y <= 6; y++)
					if (u.in(x, y) && v.in(x, y)) c++;

				if (c >= 2) isect[i][j] = isect[j][i] = 1;
			}
		}

// --- Bruteforce

		for (int srow = 1; srow <= 6; srow++)
		for (int scol = 1; scol <= 6; scol++) {

			// --- find endpoint, check path

			int erow = srow, ecol = scol, okay = 1;
			memset(block, 0, sizeof(block));
			for (int i = 0; ; i++) {

				for (int d = 0; d < 4; d++) {
					int rr = erow + "1102"[d] - '1';
					int cc = ecol + "0211"[d] - '1';
					if (block[erow][ecol][rr][cc] == 0)
						block[erow][ecol][rr][cc] = 2;
					if (block[rr][cc][erow][ecol] == 0)
						block[rr][cc][erow][ecol] = 2;
				}


				if (path[i] == 0) break;
				int r1 = erow + c2dy[path[i]];
				int c1 = ecol + c2dx[path[i]];
				if (r1 < 1 || c1 < 1 || r1 > 6 || c1 > 6) { okay=0; break; }

				block[erow][ecol][r1][c1] = 1;
				block[r1][c1][erow][ecol] = 1;

				erow = r1; ecol = c1;
			}
			if (!okay) continue;

			// --- determine walls conflicting with the path
			//     and "potential" walls (WLOG there must be a solution
			//     in which each wall will be touching the path)

			static int bad_wall[512];
			memset(bad_wall, 0, sizeof(bad_wall));

			for (int ui = 0; ui < N; ui++) {
				Wall &u = walls[ui];
				int potential = 0;

				if (u.y1 == u.y2) {
					for (int t = u.x1+1; t <= u.x2; t++) {
						if (block[u.y1][t] [u.y1+1][t] == 1) bad_wall[ui] = 1;
						if (block[u.y1][t] [u.y1+1][t] == 2) potential = 1;
					}
				} else {
					for (int t = u.y1+1; t <= u.y2; t++) {
						if (block[t][u.x1] [t][u.x1+1] == 1) bad_wall[ui] = 1;
						if (block[t][u.x1] [t][u.x1+1] == 2) potential = 1;
					}
				}

				if (potential == 0) bad_wall[ui] = 1;
			}

			// --- brute force walls

			memset(block, 0, sizeof(block));
			block_id = 1;

			for (int r1 = 0; r1 < 8; r1++)
			for (int c1 = 0; c1 < 8; c1++)
			for (int r2 = 0; r2 < 8; r2++)
			for (int c2 = 0; c2 < 8; c2++)
				if (r2 < 1 || c2 < 1 || r2 > 6 || c2 > 6)
					block[r1][c1][r2][c2] = 1<<30;

			for (int w1 = 0; w1 < N; w1++) if (!bad_wall[w1] && walls[w1].len == len[0])
			for (int w2 = w1+1; w2 < N; w2++) if (!bad_wall[w2] && walls[w2].len == len[1] && !isect[w1][w2])
			for (int w3 = w2+1; w3 < N; w3++) {
				if (walls[w3].len < len[2]) continue;
				if (walls[w3].len > len[2]) break;

				if (bad_wall[w3]) continue;
				if (isect[w1][w3] || isect[w2][w3]) continue;

				// --- marked blocked moves
				block_id++;
				for (int i = 0; i < 3; i++) {
					Wall &u = walls[i==0 ? w1 : (i==1 ? w2 : w3)];

					if (u.y1 == u.y2) {
						for (int t = u.x1+1; t <= u.x2; t++) {
							block[u.y1][t] [u.y1+1][t] = block_id;
							block[u.y1+1][t] [u.y1][t] = block_id;
						}
					} else {
						for (int t = u.y1+1; t <= u.y2; t++) {
							block[t][u.x1] [t][u.x1+1] = block_id;
							block[t][u.x1+1] [t][u.x1] = block_id;
						}
					}
				}

				// find shortest path

				static int qdata[10000], dist[8][8];
				int *qh = qdata, *qt = qdata;
                                *qt++ = srow; *qt++ = scol;

                                memset(dist, 0x3f, sizeof(dist));
                                dist[srow][scol] = 0;

                                while (qh < qt) {
                                	int r = *qh++; int c = *qh++;
                                	if (r == erow && c == ecol) break;
                                	for (int d = 0; d < 4; d++) {
                                		int r1 = r + "0211"[d] - '1';
                                		int c1 = c + "1102"[d] - '1';
                                		if (block[r][c][r1][c1] >= block_id) continue;
                                		if (dist[r1][c1] < 1000) continue;

                                		dist[r1][c1] = dist[r][c] + 1;
                                                *qt++ = r1; *qt++ = c1;
					}
				}

				if (dist[erow][ecol] == pathlen) {

//OUTPUT GEN CODE
printf("%d %d\n", scol, srow);
printf("%d %d\n", ecol, erow);

Wall out[3] = { walls[w1], walls[w2], walls[w3] };
int shown[3]={0,0,0};
for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++)
		if (out[j].len == len_orig[i] && !shown[j]) {
			shown[j] = 1;
			Wall &u = out[j];
			printf("%d %d %d %d\n", u.x1, u.y1, u.x2, u.y2);
			break;
		}
}
//ENF OF OUTPUT
					goto FOUND;
				}
			} //for(w1,w2,w3)
		} //for(srow,scol)
FOUND:;
	}//while(scanf)
}
