#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

#define MAXN 110000

char S[MAXN];
int N;
int sa[MAXN], key[MAXN], pos[MAXN], bsize[MAXN];

struct Comparer {
	bool operator()(int i, int j) const {
		return key[i] < key[j];
	}
};

void build()
{
	int i, j, k;

	N = strlen(S);

	for (i = 0; i < N; i++) {
		sa[i] = i;
		key[i] = S[i];
	}
	sort(sa, sa+N, Comparer());

	for (i = 0; i < N; i = j) {
		for (j = i + 1; j < N && S[sa[j]] == S[sa[i]]; j++);
		bsize[i] = j - i;
	}

	for (int H = 1; H < N; H *= 2) {
		for (i = 0; i < N; i += bsize[i]) {
			for (j = 0; j < bsize[i]; j++)
				pos[sa[i + j]] = i;
		}

		for (i = 0; i < N; i++) {
			key[i] = (i + H < N ? pos[i + H] : -1);
		}

		for (i = 0; i < N;) {
			k = i + bsize[i];
			sort(sa+i, sa+k, Comparer());
			while (i < k) {
				for (j = i + 1; j < k && key[sa[i]] == key[sa[j]]; j++);
				bsize[i] = j - i;
				i = j;
			}
		}
	}

	/*printf("S=%s\n", S);
	for (i = 0; i < N; i++)
		printf("%3d sa=%-2d %s\n", i, sa[i], S+sa[i]);*/
}

bool query(char *pattern)
{
	int len = strlen(pattern);
	if (len == 0) return true;

	int left = 0, right = N-1;
	while (left <= right) {
		int mid = (left + right) / 2;
		int t = memcmp(S + sa[mid], pattern, len);
		if (t == 0)
			return true;
		else if (t < 0)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return false;
}

int main()
{
	char buf[10000];
	int T, Q;

	gets(buf);
	sscanf(buf, "%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		gets(S);

		gets(buf);
		sscanf(buf, "%d", &Q);

		build();

		for (int q = 1; q <= Q; q++) {
			gets(buf);
			if (query(buf))
				printf("y\n");
			else
				printf("n\n");
		}
	}
}
