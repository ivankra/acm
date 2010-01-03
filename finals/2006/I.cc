#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
using namespace std;

int main() {
	int N, M;
	for (int cs = 1; cin >> N >> M; cs++) {
		if (N == 0) break;

		int adj[64][64];
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				adj[i][j] = (i==j ? 0 : 999999);

		map<string, int> mp;
		for (int i = 0; i < M; i++) {
			string s, t;
			cin >> s >> t;

			if (mp.count(s) == 0) { int k = mp.size(); mp[s] = k; }
			if (mp.count(t) == 0) { int k = mp.size(); mp[t] = k; }

			if (s != t)
				adj[mp[s]][mp[t]] = adj[mp[t]][mp[s]] = 1;
		}

		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
		
		int res = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				res = max(res, adj[i][j]);

		printf("Network %d: ", cs);
		if (res > N)
			printf("DISCONNECTED\n\n");
		else
			printf("%d\n\n", res);
	}
}
