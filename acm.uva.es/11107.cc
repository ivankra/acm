#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

struct Node {
	char *s;
	int len;
	Node *kid, *sib;
	int count, last;

	Node(char *S, int L) : s(S), len(L), kid(NULL), sib(NULL), count(0), last(-1) { }
	~Node() {
		if (kid != NULL) delete kid;
		if (sib != NULL) delete sib;
	}
};

char dna[101][1024];
int N;

void insert(Node *p, char *s, int id) {
	while (*s) {
		Node *q;
		for (q = p->kid; q != NULL && q->s[0] != s[0]; q = q->sib);

		if (q == NULL) {
			q = new Node(s, strlen(s));
			q->count = 1;
			q->last = id;
			q->sib = p->kid;
			p->kid = q;
			return;
		}

		int m;
		for (m = 0; m < q->len && q->s[m] == s[m]; m++);

		if (m < q->len) {
			Node *r = new Node(q->s+m, q->len-m);
			r->count = q->count;
			r->last = q->last;
			r->kid = q->kid;
			r->sib = NULL;
			q->kid = r;
			q->len = m;
		}

		if (q->last != id) {
			q->last = id;
			q->count++;
		}

		p = q;
		s += m;
	}
}

int findMax(Node *p) {
	int res = 0;
	for (Node *q = p->kid; q != NULL; q = q->sib) {
		if (2*q->count > N)
			res >?= q->len + findMax(q);
	}
	return res;
}

char path[1024];
int pathLen, maxLen;

void printMax(Node *p) {
	if (pathLen >= maxLen) {
		path[pathLen] = 0;
		printf("%s\n", path);
		return;
	}

	Node *kid[26];
	for (int i = 0; i < 26; i++) kid[i] = NULL;

	for (Node *q = p->kid; q != NULL; q = q->sib)
		kid[q->s[0]-'a'] = q;

	for (int i = 0; i < 26; i++) {
		if (kid[i] != NULL && 2*kid[i]->count > N) {
			int tmp = pathLen;
			for (int j = 0; j < kid[i]->len; j++)
				path[pathLen++] = kid[i]->s[j];
			printMax(kid[i]);
			pathLen = tmp;
		}
	}
}

int main()
{
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		if (cs > 1) printf("\n");

		Node *root = new Node("", 0);

		for (int i = 0; i < N; i++) {
			scanf(" %s", dna[i]);
			for (int j = 0; dna[i][j]; j++)
				insert(root, dna[i]+j, i);
		}

		root->count = N;

		maxLen = findMax(root);
		if (maxLen < 1) {
			printf("?\n");
		} else {
			pathLen = 0;
			printMax(root);
		}

		delete root;
	}
}
