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
#include <map>
using namespace std;

struct Tree {
	int N;
	char label[128];
	vector<int> adj[128];

	void clear() {
		N = 0;
		for (int i = 0; i < 128; i++) {
			label[i] = 0;
			adj[i].clear();
		}
	}
};

int read(Tree &t, int parent) {
	int x = t.N++;
	if (parent >= 0) t.adj[x].push_back(parent);

	char ch;
	scanf(" %c %c", &t.label[x], &ch);

	if (ch != '(') {
		ungetc(ch, stdin);
		return x;
	}

	for (;;) {
		t.adj[x].push_back(read(t, x));
		if (scanf(" %c", &ch) != 1 || ch != ',') break;
	}

	return x;
}

void readTree(Tree &t) {
	t.clear();
	read(t, -1);
}

map<vector<int>, int> mp;

int encode(const Tree &t, int x, int parent = -1) {
	vector<int> v;

	if (parent < 0) {
		for (int i = 0; i < (int)t.adj[x].size(); i++) {
			int y = t.adj[x][i];
			if (y == parent) continue;
			v.push_back(encode(t, y, x));
		}

		int best = 0;
		int m = v.size();
		for (int s = 1; s < m; s++) {
			for (int i = best, j = s, k = 0; k < m; k++) {
				if (v[i] != v[j]) {
					if (v[j] < v[i]) best = s;
					break;
				}
				if (++i >= m) i = 0;
				if (++j >= m) j = 0;
			}
		}
		rotate(v.begin(), v.begin()+best, v.end());
	} else {
		int i;
		for (i = 0; t.adj[x][i] != parent; i++);

		for (;;) {
			if (++i >= (int)t.adj[x].size()) i = 0;
			int y = t.adj[x][i];
			if (y == parent) break;
			v.push_back(encode(t, y, x));
		}
	}

	v.push_back(t.label[x]);

	int k;
	if (mp.count(v) > 0) {
		k = mp[v];
	} else {
		k = mp.size();
		mp[v] = k;
	}

#if 0
	printf("%c {", t.label[x]);
	for (int i = 0; i < (int)v.size(); i++)
		printf(" %d", v[i]);
	printf("} => %d\n", k);
#endif

	return k;
}

bool solve(Tree &T1, Tree &T2) {
	if (T1.N != T2.N) return false;

	mp.clear();
	for (int i = 0; i < T1.N; i++)
		if (encode(T1, i, -1) == encode(T2, 0, -1)) return true;
	return false;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		Tree T1, T2;
		readTree(T1);
		readTree(T2);
		printf(solve(T1, T2) ? "same\n" : "different\n");
	}
}
