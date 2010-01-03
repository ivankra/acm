#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <string>
#include <algorithm>
using namespace std;

int adj[16][16], ncc, ccid[16], in[16], out[16];

void euler(int x, string &str) {
	while (out[x] > 0) {
		int y;
		for (y = 0; y <= 9 && adj[x][y] == 0; y++);
		assert(y <= 9 && adj[x][y] > 0);
		adj[x][y]--; out[x]--; in[y]--;
		euler(y, str);
		str += (char)(y + '0');
	}
}

void fw() {
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));

	int w[16][16];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			w[i][j] = (adj[i][j] > 0 || adj[j][i] > 0);
			out[i] += adj[i][j];
			in[j] += adj[i][j];
		}
		w[i][i] = 1;
	}

	for (int k = 0; k < 10; k++)
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				w[i][j] |= w[i][k] & w[k][j];

	memset(ccid, 0xff, sizeof(ccid));
	ncc = 0;

	for (int i = 0; i < 10; i++) {
		if (ccid[i] >= 0) continue;
		if (out[i] == 0 && in[i] == 0) continue;
		for (int j = 0; j < 10; j++)
			if (w[j][i]) ccid[j] = ncc;
		ncc++;
	}
}

string solve(int n, int m) {
	if (n > m) return "";

	assert(10 <= n && n <= m && m <= 99);

	memset(adj, 0, sizeof(adj));
	for (int i = n; i <= m; i++)
		adj[i/10][i%10]++;

	for (;;) {
		fw();
		if (ncc <= 1) break;

		int x = -1, y = -1;
		for (int i = 0; i < 10; i++) {
			if (ccid[i] == 0 && (x<0 || out[i]<in[i])) x = i;
			if (ccid[i] > 0 && (y<0 || out[i]>in[i])) y = i;
		}
		assert(x >= 0 && y >= 0);
		adj[x][y]++;
	}
/*
printf("old graph\n");
for (int x = 0; x <= 9; x++)
for (int y = 0; y <= 9; y++)
  if (adj[x][y] > 0) printf("%d -> %d  x %d\n", x, y, adj[x][y]);
*/
	int cnt = 0;
	for (int i = 0; i < 10; i++) cnt += abs(in[i] - out[i]);

	for (int x = 0; x < 10 && cnt > 2; x++)
		for (int y = 0; y < 10 && cnt > 2; y++)
			while (cnt > 2 && out[x] < in[x] && out[y] > in[y]) {
				adj[x][y]++;
				out[x]++;
				in[y]++;
				cnt -= 2;
			}
	fw();
/*
printf("graph\n");
for (int x = 0; x <= 9; x++)
for (int y = 0; y <= 9; y++)
  if (adj[x][y] > 0) printf("%d -> %d  x %d\n", x, y, adj[x][y]);
for (int x = 0; x <= 9; x++)
  if (in[x] != 0 || out[x] != 0) printf("vertex %d: in=%d out=%d\n", x, in[x], out[x]);
*/
	string res = "";
	for (int x = 0, k = 0; x <= 9; x++) {
		if (in[x] < out[x]) {
			assert(in[x] == out[x] - 1 && ++k == 1);
			euler(x, res);
			res += (char)('0' + x);
		}
	}
	for (int x = 0; x <= 9; x++) {
		if (in[x] != 0 || out[x] != 0) {
			assert(in[x] == out[x]);
			euler(x, res);
			res += (char)('0' + x);
		}
	}
	reverse(res.begin(), res.end());	
	return res;
}

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		string s = solve(max(n, 10), m);
		for (int i = n; i <= 9 && i <= m; i++)
			if (strchr(s.c_str(), '0'+i)==NULL) s += (char)('0'+i);

		for (int i = n; i <= m; i++) {
			char t[10];
			sprintf(t, "%d", i);
			assert(strstr(s.c_str(), t) != NULL);
		}

		printf("%s\n", s.c_str());
	}
}
