// An implementation of a binomial heap.
// Binomial heaps provide the following operations in O(log n) time
// insert element, get/erase minimum, merge two heaps (destructive).
#include <cstdio>
#include <cassert>
#include <queue>
#include <algorithm>
using namespace std;
#define TEST

template<typename Tp> class binomial_heap {
        // A k-degree binomial tree contains k children of degrees 0, 1, ..., k-1.
        // Children are sorted in decreasing order of degrees.
        struct Node {
                Tp key;  char deg;  Node *kid, *sib;
                Node(const Tp &k) : key(k), deg(0), kid(NULL), sib(NULL) {}
                ~Node() { if (kid) delete kid; if (sib) delete sib; }
        };

        // A binomial heap is a collection of several binomial trees
        // of distinct degrees, represented here as a linked list of trees,
        // linked by their 'sib' field. The trees in the list are
        // sorted in decresing order of their degrees.

        Node *head;
        int _size;

        // Merges (destructively) two trees of the same degree d
        // to form a tree of degree d+1.
        static Node *pair(Node *p, Node *q) {
                assert(p != NULL && q != NULL); assert(p->deg == q->deg);
                if (q->key < p->key) swap(p, q);
                q->sib = p->kid; p->kid = q; p->sib = 0; p->deg++;
                return p;
        }

        // Reverses a linked list of trees
        static Node *reverse(Node *p) {
                Node *r = NULL, *q;
                while (p) { q = p->sib; p->sib = r; r = p; p = q; }
                return r;
        }

        // Merges two heaps (linked lists of trees)
        static Node *merge(Node *p, Node *q) {
                Node *res = NULL, *carry = NULL, *pnext;
                for (p = reverse(p), q = reverse(q); p || q;) {
                        if (p == NULL || (q != NULL && q->deg < p->deg)) swap(p, q);
                        pnext = p->sib;
                        if (carry == NULL) {
                            carry = p; carry->sib = NULL; p = pnext;
                        } else if (carry->deg < p->deg) {
                            carry->sib = res; res = carry; carry = NULL;
                        } else if (carry->deg == p->deg) {
                            carry = pair(carry, p); p = pnext;
                        } else {
                            p->sib = res; res = p; p = pnext;
                        }
                }
                if (carry != NULL) { carry->sib = res; res = carry; }
                return res;
        }

        Node **ppMinNode() {
                Node **r = &head;
                if (head == NULL) return r;
                for (Node *p = head; p->sib != NULL; p = p->sib)
                        if (p->sib->key < (*r)->key) r = &p->sib;
                return r;
        }

public:
        void merge(binomial_heap<Tp> &H) {
                head = merge(head, H.head);
                _size += H._size;
                H.head = NULL; H._size = 0;
        }

        int size() const { return _size; }
        bool empty() const { return head==NULL; }
        void push(const Tp &k) { head = merge(head, new Node(k)); _size++; }

        Tp pop() {
                assert(!empty());
                Node **pp = ppMinNode();
                Node *p = *pp;
                *pp = p->sib;
                head = merge(head, p->kid);
                p->sib = p->kid = NULL;
                Tp x = p->key;
                delete p;
                _size--;
                return x;
        }

        const Tp &top() { assert(!empty()); return (*ppMinNode())->key; }

        binomial_heap() { head = NULL; _size = 0; }
        ~binomial_heap() { if (head) delete head; }

private:
        binomial_heap(const binomial_heap &H) {}
        binomial_heap &operator =(const binomial_heap &H) {}
};

#ifdef TEST
int main() {
        binomial_heap<int> h;
        priority_queue<int> pq;
        int N = 10000000;
        for (int i = 0; i < N; i++) {
                if(i%1000==0){printf("\r%.0lf%% complete", i/(N+0.)*100);fflush(stdout);}
                //h.verify();
                assert(h.size() == (int)pq.size());
                if (h.size()==0 || (rand()%100) < 50) {
                        int x = rand() % 1000; h.push(x); pq.push(-x);
                } else {
                        int x = h.pop(), y = -pq.top();
                        pq.pop(); assert(x == y);
                }
        }
        printf("\n\033[01;32mPASS\033[m\n"); exit(0);
}
#endif
