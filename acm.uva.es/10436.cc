#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

#define REP(V,N) for(int(V)=0,REP_N=(int)(N);(V)<REP_N;(V)++)
#define INF 0x3fffffff

int N, vcost[50], dist[50][50], next[50][50];
string name[50];
map<string, int> id;

int main() {
	int T, M;
	string s, t;

	cin >> T;

	for (int cs = 1; cs <= T; cs++) {
		if (cs > 1) printf("\n");
		printf("Map #%d\n", cs);

		cin >> N;
		id.clear();
		REP(i,N) {
			cin >> name[i] >> vcost[i];
			id[name[i]] = i;
		}

		REP(i,N) REP(j,N) {
			dist[i][j] = i==j ? 0 : INF;
			next[i][j] = j;
		}

		cin >> M;
		REP(i,M) {
			int d;
			cin >> s >> t >> d;
			int x = id[s], y = id[t];
			dist[x][y] = dist[y][x] = min(dist[x][y], d);
		}

		REP(i,N) REP(j,N)
			if (dist[i][j] < INF)
				dist[i][j] = 2*dist[i][j] + vcost[j];

		REP(k,N) REP(i,N) REP(j,N) {
			if (dist[i][k] + dist[k][j] < dist[i][j]) {
				dist[i][j] = dist[i][k] + dist[k][j];
				next[i][j] = next[i][k];
			}
		}

		cin >> M;
		for (int i = 1; i <= M; i++) {
			int npass;
			printf("Query #%d\n", i);
			cin >> s >> t >> npass;
			printf("%s", s.c_str());

			int x = id[s], y = id[t];
			double z = (dist[x][y] + vcost[x]) * 1.1 / npass;
			do { x = next[x][y]; printf(" %s", name[x].c_str()); } while (x != y);
			printf("\n");

			printf("Each passenger has to pay : %.2f taka\n", z+1e-9);
		}
	}
}
