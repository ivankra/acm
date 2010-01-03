// answer is provably always "Yes":
// repeatedly halve the size of the problem by merging together
// pairs of even/even and odd/odd values.
#include <cstdio>

struct Node {
	Node *left, *right;
	int value;
};

Node buffer[2048*4+10];
int used, first;

Node *create(int value, Node *l, Node *r) {
	Node *p = &buffer[++used];
	p->value = value;
	p->left = l;
	p->right = r;
	return p;
}

Node *join(Node *l, Node *r) {
	return create((l->value + r->value) / 2, l, r);
}

void prn(Node *p) {
	if (p->left == 0) {
		printf(first ? "%d" : " %d", p->value);
		first = 0;
	} else {
		prn(p->left);
		prn(p->right);
	}
}

int main()
{
	int i, j, x, N;
	Node *a[2048];

	while (scanf("%d", &N) == 1 && N > 0) {
		used = 0;
		N = 2*N-1;
		for (i = 0; i < N; i++) {
			scanf("%d", &x);
			a[i] = create(x, 0, 0);
		}

		while (N > 1) {
			Node *even = 0, *odd = 0;
			j = 0;
			for (i = 0; i < N; i++) {
				Node *p = a[i];
				if (p->value % 2 == 0) {
					if (even == 0) {
						even = p;
					} else {
						a[j++] = join(even, p);
						even = 0;
					}
				} else {
					if (odd == 0) {
						odd = p;
					} else {
						a[j++] = join(odd, p);
						odd = 0;
					}
				}
			}
			N = j;
		}

		first = 1;
		printf("Yes\n");
		prn(a[0]);
		printf("\n");
	}
}
