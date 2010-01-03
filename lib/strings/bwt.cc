// Burrows-Wheeler transform in O(n log^2 n)
// Reads from stdin, writes BWT data to stdout, stats and row number to stderr
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef unsigned char byte;

byte *text;
int N, *sa, *rank, *key;

struct Cmp {
	bool operator()(int i, int j) const { return key[i] < key[j]; }
};

void build()
{
	int i, j, k;

	for (i = 0; i < N; i++) {
		sa[i] = i;
		key[i] = text[i];
	}
	sort(sa, sa+N, Cmp());

	for (i = 0; i < N; i++)
		rank[sa[i]] = (i != 0 && text[sa[i-1]] == text[sa[i]]) ? rank[sa[i-1]] : i;

	for (int phase = 1; phase < N; phase *= 2) {
		for (i = 0; i < N; i = j) {
			for (j = i; j < N && rank[sa[i]] == rank[sa[j]]; j++) {
				k = sa[j] + phase;
				if (k >= N) k -= N;
				key[sa[j]] = rank[k];
			}

			if (j - i != 1) {
				sort(sa+i, sa+j, Cmp());
				for (k = i; k < j; k++)
					rank[sa[k]] = (k > i && key[sa[k-1]] == key[sa[k]]) ? rank[sa[k-1]] : k;
			}
		}
	}
}

int main()
{
	int size = 1024, c;
	text = (byte *)malloc(size);
	N = 0;
	while ((c = getchar()) != EOF) {
		if (N+1 == size) {
			size *= 2;
			text = (byte *)realloc(text, size);
			if (text == NULL) {
				fprintf(stderr, "Out of memory\n");
				exit(1);
			}
		}
		text[N++] = c;
	}

	sa = (int *)malloc(N * sizeof(int));
	rank = (int *)malloc(N * sizeof(int));
	key = (int *)malloc(N * sizeof(int));
	if (sa == NULL || rank == NULL || key == NULL) {
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}

	double t = clock();
	build();
	t = (clock() - t) / CLOCKS_PER_SEC;
	fprintf(stderr, "(Suffix array construction took %.3f seconds.)\n", t);

	for (int i = 0; i < N; i++) {
		putchar(sa[i] == 0 ? text[N-1] : text[sa[i]-1]);
		if (sa[i] == 1) {
			fprintf(stderr, "%d\n", i);
		}
	}
}
