#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;

#define MAX 100000

char text[MAX];
int N, sa[MAX], rank[MAX];

void build()
{
	static int cnt[MAX], sa2[MAX], key[MAX];
	int i, j, k, m;

	memset(cnt, 0, 256*sizeof(int));
	for (i = 0; i < N; i++) ++cnt[(unsigned char)text[i]];
	for (i = 0; i < 255; i++) cnt[i+1] += cnt[i];
	for (i = 0; i < N; i++) sa[--cnt[(unsigned char)text[i]]] = i;
	for (i = 0; i < N; i = j) {
		for (j = i + 1; j < N && text[sa[i]] == text[sa[j]]; j++);
		for (k = i; k < j; k++) rank[sa[k]] = i;
	}

	for (m = 1; m < N; m *= 2) {
		memset(cnt, 0, (N+1)*sizeof(int));
		for (i = 0; i < N; i++) ++cnt[key[i] = i+m < N ? 1+rank[i+m] : 0];
		for (i = 0; i < N; i++) cnt[i+1] += cnt[i];
		for (i = 0; i < N; i++) sa2[--cnt[key[sa[i]]]] = sa[i];

		memset(cnt, 0, (N+1)*sizeof(int));
		for (i = 0; i < N; i++) ++cnt[rank[sa2[i]]];
		for (i = 0; i < N; i++) cnt[i+1] += cnt[i];
		for (i = N-1; i >= 0; i--) sa[--cnt[rank[sa2[i]]]] = sa2[i];

		for (i = 0; i < N; i = j) {
			for (j = i+1; j < N && rank[sa[j]] == rank[sa[i]] && key[sa[j]] == key[sa[i]]; j++);
			for (k = i; k < j; k++) rank[sa[k]] = i;
		}
	}
}


int main()
{
	int c;
	N = 0;
	while (N+1 < MAX && (c = getchar()) != EOF) {
		if (isalpha(c)) text[N++] = c;
	}
	text[N] = 0;

	double t = clock();
	build();
	t = (clock() - t) / (double)(CLOCKS_PER_SEC);
	printf("N=%d time=%.3fs\n", N, t);

	for (int i = 0; i < N; i++) {
//		printf("%s\n", text + sa[i]);
		if (i > 1) assert(strcmp(text + sa[i-1], text + sa[i]) < 0);
	}
	printf("OK\n");
}
