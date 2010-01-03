#include <cstdio>

struct Trie {
	Trie *kid, *sib;
	char c;
	Trie(char c_) : kid(NULL), sib(NULL), c(c_) {}
};

Trie *insert(Trie *x, const char *s)
{
	Trie *y;
	for (int i = 0; s[i]; i++) {
		for (y = x->kid; y != NULL && y->c != s[i]; y = y->sib);
		if (y == NULL) {
			y = new Trie(s[i]);
			y->sib = x->kid;
			x->kid = y;
		}
		x = y;
	}
	return x;
}

int main()
{
	Trie *root = new Trie(0);
	insert(root, "alpha");
	insert(root, "beta");
}
