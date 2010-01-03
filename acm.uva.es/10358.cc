#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

#define MAX_STATES 50000

char maze[8][8];

struct State {
	char loc[3];	// M,A,A
	char turn;

	bool operator <(const State &other) const {
		for (int i = 0; i < 3; i++)
			if (loc[i] != other.loc[i])
				return loc[i] < other.loc[i];
		return turn < other.turn;
	}
};

State V[MAX_STATES];
int status[MAX_STATES], N;
short stateMap[64][64][64][2];
vector<int> adj[MAX_STATES], rev_adj[MAX_STATES];

int getStateId(State s) {
	if (s.loc[1] > s.loc[2]) swap(s.loc[1], s.loc[2]);
	return stateMap[s.loc[0]][s.loc[1]][s.loc[2]][s.turn];
}

int dx[] = { 0, 1, -1, 0, 0 };
int dy[] = { 0, 0, 0, 1, -1 };

bool move(char &i, int dir) {
	int y = i / 8 + dy[dir];
	int x = i % 8 + dx[dir];
	if (y < 0 || y >= 8 || x < 0 || x >= 8 || maze[y][x] == '#') {
		return false;
	} else {
		i = y * 8 + x;
		return true;
	}
}

void genMoves(int i)
{
	int j;
	State s;
	if (V[i].turn == 0) {
		for (int dir = 0; dir < 5; dir++) {
			s = V[i];
			if (!move(s.loc[0], dir)) continue;
			s.turn = 1;
			j = getStateId(s);
			adj[i].push_back(j);
			rev_adj[j].push_back(i);
		}
	} else {
		for (int dir1 = 0; dir1 < 5; dir1++) {
			for (int dir2 = 0; dir2 < 5; dir2++) {
				s = V[i];
				if (!move(s.loc[1], dir1)) continue;
				if (!move(s.loc[2], dir2)) continue;
				s.turn = 0;
				j = getStateId(s);
				adj[i].push_back(j);
				rev_adj[j].push_back(i);
			}
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		State source;
		source.turn = 0;
		for (int i = 0, k = 1; i < 64; i++) {
			char c;
			scanf(" %c", &c);
			maze[i/8][i%8] = c;
			if (c == 'A')
				source.loc[k++] = i;
			else if (c == 'M')
				source.loc[0] = i;
		}

		N = 0;

		for (int i = 0; i < 64; i++) {
			if (maze[i/8][i%8] == '#') continue;
			for (int j = 0; j < 64; j++) {
				if (maze[j/8][j%8] == '#') continue;
				for (int k = j; k < 64; k++) {
					if (maze[k/8][k%8] == '#') continue;
					for (int t = 0; t < 2; t++) {
						State s;
						assert(N < MAX_STATES);
						s.loc[0] = i;
						s.loc[1] = j;
						s.loc[2] = k;
						s.turn = t;
						stateMap[i][j][k][t] = N;
						stateMap[i][k][j][t] = N;
						V[N] = s;
						N++;
					}
				}
			}
		}

		for (int i = 0; i < N; i++) {
			adj[i].clear();
			rev_adj[i].clear();
		}

		for (int i = 0; i < N; i++) {
			genMoves(i);
		}

		queue<int> Q;
		for (int i = 0; i < N; i++) {
			State s = V[i];
			if (maze[s.loc[0]/8][s.loc[0]%8] == 'P') {
				status[i] = s.turn == 0 ? 1 : 0;
			} else if (s.loc[0] == s.loc[1] || s.loc[0] == s.loc[2]) {
				status[i] = s.turn == 0 ? 0 : 1;
			} else {
				status[i] = -2;
				Q.push(i);
			}
		}

		int src = getStateId(source);
		while (!Q.empty() && status[src] < 0) {
			int s = Q.front();
			Q.pop();

			assert(status[s] == -2);

			status[s] = 0;
			for (int i = 0; i < (int)adj[s].size(); i++) {
				int t = adj[s][i];
				if (status[t] == 0) {
					status[s] = 1;
					break;
				} else if (status[t] < 0) {
					status[s] = -1;
				}
			}

			if (status[s] != -1) {
				for (int i = 0; i < (int)rev_adj[s].size(); i++) {
					int t = rev_adj[s][i];
					if (status[t] == -1) {
						status[t] = -2;
						Q.push(t);
					}
				}
			}
		}

		if (status[src] < 0) {
			printf("You are trapped in the Matrix.\n");
		} else if (status[src] == 0) {
			printf("You are eliminated.\n");
		} else {
			printf("You can escape.\n");
		}
	}
}
