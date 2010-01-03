#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <windows.h>
using namespace std;

struct Node {
	Node *next[26], *fail, *go[26];

	Node() {
		memset(next, 0, sizeof(next));
	}
};

void insert(Node *p, const char *s) {
	for (; *s; ++s) {
		int c = *s - 'a';
		if (p->next[c] == NULL) {
			p->next[c] = new Node();
		}
		p = p->next[c];
	}
	//TODO:
}

void build(Node *root)
{
	vector<Node *> v;
	v.push_back(root);
	root->fail = root;

	// Build failure transitions
	for (int i = 0; i < (int)v.size(); ++i) {
		Node *p = v[i];
		for (int c = 0; c < 26; ++c) {
			Node *q = p->next[c];
			if (q == NULL) continue;
			Node *f = p->fail;
			while (f->next[c] == NULL && f != root)
				f = f->fail;
			q->fail = (f->next[c] == NULL ? root : f->next[c]);
			v.push_back(q);
		}
	}

	for (int i = 0; i < (int)v.size(); ++i) {
		Node *p = v[i];
		for (int c = 0; c < 26; c++) {
			Node *q = p;
			while (q->next[c] == NULL && q != root)
				q = q->fail[c];
			p->go[c] = (q->next[c] == NULL ? root : q->next[c]);
		}
	}
}

int main()
{
	//TODO: testing!

}
