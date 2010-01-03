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

string name[600];
int cost[600][600], N;

int seen[600000], prev[600000], seen_id = 42;
int queue_buf[600*1001];

int encode(int x, int v) { return (x << 10) + v; }

bool bfs(int src, int dst)
{
	seen_id++;
	int *head = queue_buf, *tail = queue_buf;
	int state;
	*tail++ = encode(src, 0);
	seen[head[0]] = seen_id;
	prev[head[0]] = -1;

	while (head != tail) {
		state = *head++;
		int x = state >> 10;
		int v = state & 1023;

		if (x == dst) {
			goto done;
		}

		for (int y = 0; y < N; y++) {
			if (cost[x][y] > 1000) continue;
			if (cost[x][y] < v) continue;

			state = encode(y, max(v, cost[x][y]));
			if (seen[state] != seen_id) {
				seen[state] = seen_id;
				prev[state] = encode(x, v);
				*tail++ = state;
			}
		}
	}
	return false;

done:
	vector<string> out;
	while (true) {
		int x = state >> 10;
		if (x == src) break;
		out.push_back(name[x]);
		state = prev[state];
	}
	printf("%s", name[src].c_str());
	for (int i = out.size()-1; i >= 0; i--)
		printf(" %s", out[i].c_str());
	printf("\n");
	return true;
}

int main()
{
	int M;
	char s1[100], s2[100];
	for (int cs = 1; scanf("%d", &M) == 1 && M > 0; cs++) {
		if (cs != 1) printf("\n");
		map<string, int> mp;
		N = 0;
		memset(cost, 0x3f, sizeof(cost));
		for (int i = 0; i < M; i++) {
			int v;
			scanf(" %s %s %d", s1, s2, &v);
			if (mp.count(s1) == 0) { name[N] = s1; mp[s1] = N; N++; }
			if (mp.count(s2) == 0) { name[N] = s2; mp[s2] = N; N++; }
			int x = mp[s1];
			int y = mp[s2];
			if (v < cost[x][y]) {
				cost[x][y] = cost[y][x] = v;
			}
		}

		scanf(" %s %s", s1, s2);
		if (mp.count(s1) == 0 || mp.count(s2) == 0 || !bfs(mp[s1], mp[s2])) {
			printf("No valid route.\n");
		}
	}
}
