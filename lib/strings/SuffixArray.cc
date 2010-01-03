// O(n log^2 n) algorithm
#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 100010

char text[MAXN];
int N, sa[MAXN], lcp[MAXN], sa_key[MAXN];

struct Comparer {
	bool operator()(int i, int j) const {
		return sa_key[i] < sa_key[j];
	}
};

void build()
{
	static int pos[MAXN], bhead[MAXN];
	int i, j, k;

	// Sort and group suffixes by the first character.
	for (i = 0; i < N; i++) {
		sa[i] = i;
		sa_key[i] = text[i];
	}
	sort(sa, sa+N, Comparer());
	for (i = 0; i < N; i++) {
		bhead[i] = (i > 0 && sa_key[sa[i-1]] == sa_key[sa[i]] ? bhead[i-1] : i);
	}

	for (int m = 1; m < N; m *= 2) {
		// At this moment the suffixes are correctly sorted and grouped
		// by the first m characters. The next pass will double m.

		for (i = 0; i < N; i++)
			pos[sa[i]] = bhead[i];

		for (i = 0; i < N; i++)
			sa_key[i] = (i + m < N ? pos[i + m] : -1);

		bhead[N] = -1;
		for (i = 0; i < N; i = k) {
			for (k = i+1; bhead[i] == bhead[k]; k++);
			sort(sa+i, sa+k, Comparer());
			for (j = i+1; j < k; j++) {
				bhead[j] = (sa_key[sa[j-1]] == sa_key[sa[j]] ? bhead[j-1] : j);
			}
		}
	}

	// Construct LCP array.
	for (i = 0; i < N; i++)
		pos[sa[i]] = i;
	for (i = 0, k = 0; i < N; i++) {
		j = pos[i];
		if (j == N-1) {
			k = 0;
		} else {
			if (k != 0) k--;
			while (text[sa[j]+k] == text[sa[j+1]+k]) k++;
		}
		lcp[j] = k;
	}
}

int main()
{
	gets(text);
	N = strlen(text);

	int t = clock();
	build();
	printf("time = %.3lfs, N = %d\n", (clock()-t)/(double)CLOCKS_PER_SEC, N);

	for (int i = 0; i < N; i++)
		printf("pos=%-3d lcp=%-3d %s\n", sa[i], lcp[i], text+sa[i]);
}
