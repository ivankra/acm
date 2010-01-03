#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
	string name;
	vector<Node *> d;
	vector<string> f;
	Node *up;
	Node(string s="", Node *u=NULL) : name(s), up(u) {}
};

bool cmp(const Node *a, const Node *b) { return a->name < b->name; }

void prn(Node *x, int lev) {
	for (int i = 0; i < lev; i++) printf("|     ");
	printf("%s\n", x->name.c_str());

//	sort(x->d.begin(), x->d.end(), cmp);
	for (int i = 0; i < (int)x->d.size(); i++) prn(x->d[i], lev+1);

	sort(x->f.begin(), x->f.end());
	for (int i = 0; i < (int)x->f.size(); i++) {
		for (int j = 0; j < lev; j++) printf("|     ");
		printf("%s\n", x->f[i].c_str());
	}
}

void fre(Node *x) {
	for (int i = 0; i < (int)x->d.size(); i++) fre(x->d[i]);
	delete x;
}

int main() {
	char s[1024];
	for (int cs = 1;; cs++) {
		Node *root = new Node("ROOT"), *cur = root;

		while (scanf(" %s", s) == 1) {
			if (strcmp(s, "#") == 0) return 0;
			if (s[0] == '*') break;

			if (s[0] == 'd') {
				cur->d.push_back(new Node(s, cur));
				cur = cur->d.back();
			} else if (s[0] == ']') {
				if (cur->up != NULL) cur = cur->up;
			} else {
				cur->f.push_back(s);
			}
		}

		printf("%sDATA SET %d:\n", cs==1?"":"\n", cs);
		prn(root, 0);
		fre(root);
	}
}
