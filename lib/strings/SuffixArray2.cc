// O(n log^2 n) suffix array construction, 16 bytes/char overhead
#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

enum { MAXN = 100000 };
char text[MAXN];
long long key[MAXN];
int N, sa[MAXN], rank[MAXN], *lcp = (int *)key;

bool cmp(int i, int j) { return key[i] < key[j]; }

int main() {
	scanf("%s", text);
	N = strlen(text);

	for (int i = 0; i < N; i++) { sa[i] = i; key[i] = text[i]; }
	sort(sa, sa+N, cmp);

	for (int K = 1; ; K *= 2) {
		for (int i = 0; i < N; i++)
			rank[sa[i]] = (i > 0 && key[sa[i-1]] == key[sa[i]]) ? rank[sa[i-1]] : i;
		if (K >= N) break;
		for (int i = 0; i < N; i++)
			key[i] = rank[i] * (N+1LL) + (i+K < N ? rank[i+K]+1 : 0);
		sort(sa, sa+N, cmp);
	}

	for (int i = 0, k = 0; i < N; i++) {
		if (k > 0) k--;
		if (rank[i] == N-1) { lcp[N-1] = -1; k = 0; continue; }
		int j = sa[rank[i]+1];
		while (text[i+k] == text[j+k]) k++;
		lcp[rank[i]] = k;
	}

	for (int i = 0; i < N; i++) {
		printf("%-3d %s\n", lcp[i], text+sa[i]);
		assert(rank[sa[i]] == i); 
		if (i < N-1) {
			assert(strcmp(text+sa[i], text+sa[i+1]) < 0);
			assert(memcmp(text+sa[i], text+sa[i+1], lcp[i]) == 0);
			assert(text[sa[i]+lcp[i]] != text[sa[i+1]+lcp[i]]);
		}
	}
}
