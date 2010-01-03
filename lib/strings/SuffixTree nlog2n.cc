// Suffix tree construction in O(n log^2 n) via suffix array and lcp array
#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

#define MAX 100000
char text[MAX]; int N;

long long key[MAX];
int sa[MAX], rank[MAX], *lcp = (int *)key;

struct Cmp { bool operator()(int i, int j) const { return key[i] < key[j]; } };

void BuildSuffixArray() {
	for (int i = 0; i < N; i++) { sa[i] = i; key[i] = text[i]; }
	sort(sa, sa+N, Cmp());

	for (int k = 1; ; k *= 2) {
		for (int i = 0; i < N; i++)
			rank[sa[i]] = (i > 0 && key[sa[i-1]] == key[sa[i]]) ? rank[sa[i-1]] : i;
		if (k >= N) break;
		for (int i = 0; i < N; i++)
			key[i] = rank[i]*(N+1LL) + (i+k < N ? rank[i+k]+1 : 0);
		sort(sa, sa+N, Cmp());
	}

	for (int i = 0, m = 0; i < N; i++) {
		if (rank[i] == N-1) { lcp[N-1] = 0; m = 0; continue; }
		int j = sa[rank[i] + 1];
		while (text[i + m] == text[j + m]) m++;
		lcp[rank[i]] = m;
		if (m > 0) m--;
	}
}

struct Node {
	char *a, *b;  // [a, b) is label of the edge from parent to this node
	Node *parent, *kid, *sib;  // parent, first child, next sibling
	Node(char *a_, char *b_) {
		a = a_; b = b_; parent = NULL; kid = NULL; sib = NULL;
	}
};

Node *BuildSuffixTree() {
	Node *root = new Node(0, 0);
	Node *cur = new Node(text + sa[0], text + N);
	root->kid = cur;
	cur->parent = root;
	for (int i = 0; i < N-1; i++) {
		int u = N-sa[i]-lcp[i];
		while (u > 0) {
			if (u >= cur->b - cur->a) {
				u -= cur->b - cur->a;
				cur = cur->parent;
			} else {
				Node *mid = new Node(cur->b - u, cur->b);
				mid->kid = cur->kid;
				mid->parent = cur;
				cur->kid = mid;
				cur->b -= u;
				break;
			}
		}

		if (sa[i+1] + lcp[i] < N) {
			Node *p = new Node(text + sa[i+1] + lcp[i], text + N);
			p->parent = cur;
			p->sib = cur->kid;
			cur->kid = p;
			cur = p;
		}
	}
	return root;
}

int dump(Node *p, int &z) {
	int x = z++;
	for (Node *q = p->kid; q != NULL; q = q->sib) {
		int y = dump(q, z);
		printf("  %d -> %d [label=\"%.*s\"];\n", x, y, q->b - q->a, q->a);
	}
	return x;
}

int main()
{
	scanf("%s", text); N = strlen(text);
	text[N++] = '$';

	BuildSuffixArray();
	Node *root = BuildSuffixTree();

	printf("digraph G {\n"); {int z=1; dump(root, z);} printf("}\n");
}
