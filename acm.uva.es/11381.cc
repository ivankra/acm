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
using namespace std;
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

struct Edge {
	int x, y, cap, cost;
};

Edge E[100000];
int N, M, flowVal, flowCost;
int dist[1000], prev[1000], prevEdge[1000], INF=0x3fffffff;

void mcmf()
{
	flowVal = flowCost = 0;

	while (true) {
		for (int i = 0; i < N; i++) {
			dist[i] = INF;
			prev[i] = -1;
		}
		dist[0] = prev[0] = 0;

		bool changed;
		do {
			changed = false;
			for (int i = 0; i < M; i++) {
				if (E[i].cap > 0 && prev[E[i].x] != -1 &&
					dist[E[i].x] + E[i].cost < dist[E[i].y])
				{
					dist[E[i].y] = dist[E[i].x] + E[i].cost;
					prev[E[i].y] = E[i].x;
					prevEdge[E[i].y] = i;
					changed = true;
				}
			}
		} while (changed);

		if (prev[1] < 0) break;

		flowVal++;
		flowCost += dist[1];

		for (int x = 1; x != 0; x = prev[x]) {
			--E[prevEdge[x]].cap;
			++E[prevEdge[x] ^ 1].cap;
		}
	}
}

void add(int x, int y, int c)
{
	E[M].x = x; E[M].y = y; E[M].cap = 1; E[M].cost = c; M++;
	E[M].x = y; E[M].y = x; E[M].cap = 0; E[M].cost = -c; M++;
}

int main()
{
	int T, elegance[32][32], valid[32][32];
	char s1[2000], s2[2000];

	gets(s1);
	sscanf(s1, "%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		gets(s1); { for (int i = strlen(s1)-1; i >= 0 && isspace(s1[i]); i--) s1[i] = 0; }
		gets(s2); { for (int i = strlen(s2)-1; i >= 0 && isspace(s2[i]); i--) s2[i] = 0; }

		memset(valid, 0, sizeof(valid));
		for (int i = 0; s1[i] != 0 && s1[i+1] != 0; i++) {
			int x = s1[i] - 'a';
			int y = s1[i+1] - 'a';
			if (!valid[x][y]) {
				valid[x][y] = 1;
				elegance[x][y] = (i+1)*(i+1);
			}
		}

		int len = strlen(s2);

		N = 2 + 2*len;
		M = 0;
		for (int i = 0; i < len; i++) {
			add(0, 2+i, 0);
			add(2+len+i, 1, 0);
			for (int j = i+1; j < len; j++) {
				if (valid[s2[i]-'a'][s2[j]-'a']) {
					add(2+i, 2+len+j, elegance[s2[i]-'a'][s2[j]-'a']);
				}
			}
		}

		mcmf();
		printf("%d %d\n", len-flowVal, flowCost);
	}
}
