#include <algorithm>
#include <vector>
#include <string>
using namespace std;
typedef vector<int> VI; typedef vector<VI> VVI;

/*
 *  next[], N: a trie.  node 0 is the root.
 *  next[x][c]=0, if there's no edge (beware: the code heavily relies on this 0.)
 *
 *  fail[x]: points to a node representing longest proper suffix of x (for aho-corasick)
 *  go[x][c]: points to a node representing longest [(proper suffix of x) + c]
 *
 *  bfs[level]: BFS traversal of the trie at distance 'level' from the root.
 *
 *  seen[]: output from match()
 */

#define NODES 4096
#define ALPHA 26
struct AhoCorasick {
	int next[NODES][ALPHA], go[NODES][ALPHA], fail[NODES], seen[NODES], N;
	VVI bfs;

	AhoCorasick() {
		memset(next, 0, sizeof(next));
		N = 0;
	}

	int insert(const char *s) {
		int x = 0;
		for (; *s; s++) {
			int c = *s - 'a'; /*FIXME*/
			if (next[x][c] == 0) next[x][c] = N++;
			x = next[x][c];
		}
		return x;
	}

	void Xbfs(int x, int v) {
		bfs[v].push_back(x);
		for (int c = 0, y; c < ALPHA; c++)
			if ((y = next[x][c]) != 0) Xbfs(y, v+1);
	}

	void build() {
		bfs = VVI(N+2, VI());
		Xbfs(0, 0);
		memset(fail, 0, sizeof(fail));
		for (int v = 1; bfs[v].size() != 0; v++) {
			for (int i = 0; i < (int)bfs[v].size(); i++) {
				for (int p = bfs[v][i], c = 0; c < ALPHA; c++) {
					int x = next[p][c], y = fail[p];
					while (y > 0 && next[y][c] == 0) y = fail[y];
					fail[x] = next[y][c];
				}
			}
		}

                /* Fills array go[][] */
		for (int x = 0; x < N; x++) {
			for (int c = 0; c < ALPHA; c++) {
				int y = x;
				while (y > 0 && next[y][c] == 0) y = fail[y];
				go[x][c] = next[y][c];
			}
		}
	}

        /* Marks all nodes in the trie which occurs as substrings of s. */
	void match(const char *s) {
		for (int i = 0; i < N; i++) seen[i] = 0;

		int x = 0, c;
		for (; *s; s++) {
			c = *s-'a'; /*FIXME*/
			seen[x] = 1;
			while (x > 0 && next[x][c] == 0)
				seen[x = fail[x]] = 1;
			x = next[x][c];
		}
		seen[x] = 1;

		for (int v = N; v >= 0; v--) {
			for (int i = 0; i < (int)bfs[v].size(); i++) {
				int x = bfs[v][i];
				for (int c = 0; c < ALPHA; c++)
					if (next[x][c]) seen[x] |= seen[next[x][c]];
				seen[fail[x]] |= seen[x];
			}
		}
	}

        /* Utility */

	int find(const char *s, int x = 0) {
		for (int c; *s; s++, x=next[x][c])
			if (next[x][c=*s-'a' /*FIXME*/] == 0) return -1;
		return x;
	}


	void prn(int x=0, string s="") {
		printf("%3d. %-10s fail=%d\n", x, s.c_str(), fail[x]);
		for (int c = 0; c < ALPHA; c++)
			if (next[x][c] != 0) prn(next[x][c], s+(char)(c+'a'));
	}
};

int main() {
	VI w;

	AhoCorasick t;
/*0*/	w.push_back(t.insert("aabab"));
/*1*/	w.push_back(t.insert("aabbab"));
/*2*/	w.push_back(t.insert("abb"));
/*3*/	w.push_back(t.insert("babab"));
	t.build();

	t.prn();

	t.match("aabababb");
/* 0,2,3 */
	for (int i = 0; i < (int)w.size(); i++)
		if (t.seen[w[i]]) printf("%d ",i);
	printf("\n");
}
