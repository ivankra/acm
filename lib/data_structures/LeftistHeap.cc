#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>
using namespace std;

// Leftist heap - a mergeable priority queue.
template<typename Tp> class LeftistHeap {
	struct Node {
		Tp key;
		int d;		// d = r->d + 1;  Base case: nil->d = 0;
		Node *l, *r;

		// min-heap property: key <= l->key, key <= r->key
		// leftist property: l->d >= r->d; (implies that d is O(log N).)
	};

	Node *root, *nil;
	int _size;

	Node *create(const Tp &key) {
		Node *p = new Node();
		p->key = key;
		p->d = 1;
		p->l = p->r = nil;
		return p;		
	}

	void free(Node *p) {
		if (p != nil) {
			free(p->l);
			free(p->r);
			delete p;
		}
	}

	// O(log n)
	Node *merge(Node *x, Node *y) {
		if (x == nil) return y;
		if (y == nil) return x;

		if (y->key < x->key) swap(x, y);

		x->r = merge(x->r, y);
		if (x->r->d > x->l->d) swap(x->r, x->l);

		x->d = 1 + x->r->d;

		return x;
	}

	void init() {
		static Node _nil;
		_nil.d = 0;
		_nil.l = _nil.r = &_nil;
		nil = &_nil;
		root = nil;
		_size = 0;
	}

	LeftistHeap(const LeftistHeap &);
	void operator =(const LeftistHeap &);

public:
	struct EmptyException : std::exception {
		const char *what() const throw() { return "Heap is empty"; }
	};

	// Creates an empty heap.
	LeftistHeap() {
		init();
	}

	~LeftistHeap() {
		free(root);
	}

	// Returns true if the heap is empty, false otherwise.
	bool empty() const {
		return root == nil;
	}

	// Returns number of elements in the heap.
	int size() const {
		return _size;
	}

	// Inserts a new element.  O(log n).
	void push(const Tp &key) {
		root = merge(root, create(key));
		_size++;
	}

	// Returns the smallest element, without deleting it.
	const Tp &top() const {
		if (empty()) throw EmptyException();
		return root->key;
	}

	// Extracts the smallest element.  O(log n).
	Tp pop() {
		if (empty()) throw EmptyException();
		Tp res = root->key;
		Node *p = merge(root->l, root->r);
		delete root;
		root = p;
		_size--;
		return res;
	}

	// Merges heap will elements of heap h.
	// Heap h is emptied by the operation.
	// O(log n)
	void merge(LeftistHeap<Tp> &h) {
		root = merge(root, h.root);
		h.root = h.nil;
		_size += h._size;
		h._size = 0;
	}
};

int main()
{
	LeftistHeap<int> a, b;
	a.push(1);
	a.push(2);
	cout << a.pop() << " [1]" << endl;
	a.push(3);
	b.push(1);
	b.push(5);
	b.push(4);

	a.merge(b);
	assert(b.size() == 0);

	while (!a.empty())
		cout << a.pop() << " ";
	cout << " [1..5]" << endl;

	try {
		a.pop();
		cout << "failed to throw exception\n";
	} catch (const std::exception &e) {
		cout << e.what() << " [heap is empty]\n";
	}
}
