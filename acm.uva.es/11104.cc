#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int lcs(const string &s, const string &t) {
	static int tab[128][128];
	int n = s.size(), m = t.size();

	for (int j = 0; j <= m; j++) tab[0][j] = 0;

	for (int i = 1; i <= n; i++) {
		tab[i][0] = 0;
		for (int j = 1; j <= m; j++) {
			if (s[i-1] == t[j-1])
				tab[i][j] = 1 + tab[i-1][j-1];
			else
				tab[i][j] = max(tab[i-1][j], tab[i][j-1]);
		}
	}

	return tab[n][m];
}

int Dist[128*128*2], Queue[128*128*2], *Head, *Tail, Goal;

int State(int n, int k, int w) { return (n<<8) + (k<<1) + w; }

void Check(int s, int d) {
	if (d < Dist[s]) {
		Dist[s] = d;
		*Tail++ = s;
	}
}

int main() {
	string s, t;

	while (cin >> s >> t) {
		if (s == "0" && t == "0") break;
		if (s.size() > t.size()) swap(s, t);

		memset(Dist, 0x3f, sizeof(Dist));
		Head = Tail = Queue;
		Dist[*Tail++ = State(s.size(), lcs(s, t), 0)] = 0;
		Goal = State(t.size(), t.size(), 0);

		for (; Head < Tail && Dist[Goal] > (1<<20); Head++) {
			int n = (*Head) >> 8;
			int k = ((*Head) >> 1) & 0x7f;
			int w = (*Head) & 1;
			int D = Dist[*Head] + 1;

			Check(State(n, k, w^1), D);
			if (w == 0) {
				for (int i = (n + 1) / 2; i <= n; i++)
					Check(State(i, min(k, i), 1), D);
			} else {
				for (int i = n; i <= 2*n && i < 128; i++)
					Check(State(i, k+i-n, 0), D);
			}
		}

		cout << max(1, Dist[Goal]/2) << endl;
	}
}
