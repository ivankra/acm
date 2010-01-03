#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

struct Node {
	char c;
	Node *l, *r;

	Node(char C, Node *L = NULL, Node *R = NULL) : c(C), l(L), r(R) { }

	~Node() {
		if (l != NULL) delete l;
		if (r != NULL) delete r;
	}
};

int main()
{
	int T;
	scanf("%d", &T);

	static char buf[100000];
	for (int cs = 1; cs <= T && scanf(" %s", buf) == 1; cs++) {
		vector<Node *> v;
		for (int i = 0; buf[i]; i++) {
			if (islower(buf[i])) {
				v.push_back(new Node(buf[i]));
			} else {
				Node *b = v.back(); v.pop_back();
				Node *a = v.back(); v.pop_back();
				v.push_back(new Node(buf[i], a, b));
			}
		}
		assert(v.size() == 1);

		Node *tree = v[0];
		string res = "";

		for (int head = 0; head < (int)v.size(); head++) {
			Node *p = v[head];
			res += p->c;
			if (isupper(p->c)) {
				v.push_back(p->l);
				v.push_back(p->r);
			}
		}

		reverse(res.begin(), res.end());
		printf("%s\n", res.c_str());

		delete tree;
	}
}
