/*
ID: infnty1
PROB: starry
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef vector<string> VS;

VS strip(const VS &v) {
	int L = 999, R = 999;
	for (int i = 0; i < (int)v.size(); i++) {
		int l=0, r=0;
		while (l < (int)v[i].size() && v[i][l] == '0') l++;
		while (r < (int)v[i].size() && v[i][v[i].size()-1-r] == '0') r++;
		L <?= l;
		R <?= r;
	}

	VS res;
	for (int i = 0; i < (int)v.size(); i++) {
		if (res.size() == 0 && v[i] == string(v[i].size(), '0')) continue;
		res.push_back(v[i].substr(L, v[i].size()-L-R));
	}

	while (res.size() > 0 && res.back() == string(res.back().size(), '0'))
		res.pop_back();

	return res;
}

VS rot(const VS &v) {
	if (v.size() == 0) return v;

	int n = v.size(), m = v[0].size();
	VS w(m, string(n, '0'));;
	for (int y = 0; y < n; y++)
		for (int x = 0; x < m; x++)
			w[x][n-1-y] = v[y][x];
	return w;
}

VS flip(VS v) {
	for (int i = 0; i < (int)v.size(); i++)
		reverse(v[i].begin(), v[i].end());
	return v;
}

VS norm(VS v) {
	v = strip(v);
	VS r = v;
	for (int j = 0; j < 2; j++, v = flip(v))
		for (int i = 0; i < 4; i++, v = rot(v))
			if (v < r) r = v;
	return r;
}

void dfs1(VS &out, const VS &in, int y, int x) {
	if (y < 0 || y >= (int)in.size()) return;
	if (x < 0 || x >= (int)in[0].size()) return;
	if (out[y][x] != '0' || in[y][x] != '1') return;

	out[y][x] = '1';
	for (int dy = -1; dy <= 1; dy++)
	for (int dx = -1; dx <= 1; dx++)
		dfs1(out, in, y+dy, x+dx);
}

void dfs2(VS &a, int y, int x, char c) {
	if (y < 0 || y >= (int)a.size() ) return;
	if (x < 0 || x >= (int)a[0].size()) return;
	if (a[y][x] == c || a[y][x] == '0') return;

	a[y][x] = c;
	for (int dy = -1; dy <= 1; dy++)
	for (int dx = -1; dx <= 1; dx++)
		dfs2(a, y+dy, x+dx, c);
}

int main() {
	freopen("starry.in", "r", stdin);
	freopen("starry.out", "w", stdout);

	int w, h;
	scanf("%d %d", &w, &h);

	VS m(h, string(w, '0'));
	for (int i = 0; i < h; i++)
	for (int j = 0; j < w; j++)
		scanf(" %c", &m[i][j]);

	map<VS, char> known;

	for (int i = 0; i < h; i++)
	for (int j = 0; j < w; j++) {
		if (m[i][j] != '1') continue;

		VS v(h, string(w, '0'));
		dfs1(v, m, i, j);

		v = norm(v);
		if (known.count(v) == 0) {
			char c = 'a' + known.size();
			known[v] = c;
		}

		dfs2(m, i, j, known[v]);
	}

	for (int i = 0; i < h; i++)
		printf("%s\n", m[i].c_str());
}
