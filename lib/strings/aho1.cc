#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

struct AhoCorasick {
	struct Node { int fail, seen, next[26]; } *nodes;
	int count;
	vector<int> words;

	AhoCorasick(int n) {
		nodes = (Node *)malloc(n * sizeof(Node));
		memset(nodes, 0, n * sizeof(Node));
		count = 1;
		words.clear();
	}

	~AhoCorasick() { free(nodes); }

	int insert(const char *s) {
		int x;
		printf("insert(%s)\n", s);
		for (x = 0; islower(*s); s++) {
			if (nodes[x].next[*s-'a'] == 0)
				nodes[x].next[*s-'a'] = count++;
			x = nodes[x].next[*s-'a'];
		}
		words.push_back(x);
		return x;		
	}

	/* Computes failure links. */
	void build() {
		for (int i = 0; i < count; i++) nodes[i].fail = 0;

		printf("build()\n");

		queue<int> qp, qc;
		for (int i = 0; i < 26; i++)
			if (nodes[0].next[i] != 0) {
				qp.push(0);
				qc.push(i);
			}

		while (!qp.empty()) {
			int p = qp.front(), c = qc.front(); qp.pop(); qc.pop();
			int x = nodes[p].next[c];

			for (int i = 0; i < 26; i++)
				if (nodes[x].next[i] != 0) {
					qp.push(x);
					qc.push(i);
				}
			
			if (p == 0) continue;

			int f = nodes[p].fail;
			while (f > 0 && nodes[f].next[c] == 0) f = nodes[f].fail;

			nodes[x].fail = nodes[f].next[c];
		}
	}
	
	int matchdfs(int x) {
		for (int i = 0; i < 26; i++)
			if (nodes[x].next[i] != 0)
				nodes[x].seen |= matchdfs(nodes[x].next[i]);
		return nodes[x].seen;
	}

	/* Returns indices of words which occur as substring of s */
	vector<int> match(const char *s) {
		for (int i = 0; i < (int)words.size(); i++)
			nodes[words[i]].seen = 0;
		
		printf("match(%s)\n", s);

		int x = 0;
		for (; islower(*s); s++) {
			int c = *s - 'a';
			nodes[x].seen = 1;
			printf("x=%d c=%c\n", x, *s);
			while (x > 0 && nodes[x].next[c] == 0) {
				printf("  x=%d fail=%d\n", x, nodes[x].fail);
				x = nodes[x].fail;
				nodes[x].seen = 1;
			}
			x = nodes[x].next[c];
		}

		for (nodes[0].seen = 1; x > 0; x = nodes[x].fail)
			nodes[x].seen = 1;
		
		printf("doing matchdfs\n");
		matchdfs(0);

		vector<int> r;
		for (int i = 0; i < (int)words.size(); i++)
			if (nodes[words[i]].seen) r.push_back(i);
		return r;
	}
};

int main()
{
	AhoCorasick t(10000);
/*0*/	t.insert("aabab");
/*1*/	t.insert("aabbab");
/*2*/	t.insert("abb");
/*3*/	t.insert("babab");
	t.build();

/* 0,2,3 */	
	vector<int> w = t.match("aabababb");
	for (int i = 0; i < (int)w.size(); i++)
		printf("%d ",w[i]);
	printf("\n");
}
