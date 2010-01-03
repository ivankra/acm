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

char text[MAXN];
int N, sa[MAXN], key[MAXN];

struct Comparer {
	bool operator()(int i, int j) const {
		return key[i] < key[j];
	}
};

void buildSA()
{
	static int pos[MAXN], bhead[MAXN];
	int i, j, k;

	for (i = 0; i < N; i++) {
		sa[i] = i;
		key[i] = tolower(text[i]);
	}
	sort(sa, sa+N, Comparer());

	for (i = 0; i < N; i++) {
		bhead[i] = (i > 0 && key[sa[i-1]] == key[sa[i]] ? bhead[i-1] : i);
	}

	for (int m = 1; m < N; m *= 2) {
		for (i = 0; i < N; i++)
			pos[sa[i]] = bhead[i];

		for (i = 0; i < N; i++)
			key[i] = (i + m < N ? pos[i + m] : -1);

		bhead[N] = -1;
		for (i = 0; i < N; i = k) {
			for (k = i+1; k < N && bhead[i] == bhead[k]; k++);
			sort(sa+i, sa+k, Comparer());
			for (j = i+1; j < k; j++) {
				bhead[j] = (key[sa[j-1]] == key[sa[j]] ? bhead[j-1] : j);
			}
		}
	}
}

char ransom[30000];
int M, minCuts[30000], cutLen[30000], cutPos[30000];

void findLongestMatch(int &sufPos, int &sufLen, char *pattern)
{
	sufPos = sufLen = 0;

	int left = 0, right = N-1;
	while (left <= right) {
		int mid = (left + right) / 2;

		int i = sa[mid], m = 0;
		while (tolower(text[i+m]) == pattern[m]) m++;
		if (m > sufLen) {
			sufPos = i;
			sufLen = m;
		}

		if (pattern[m] == 0)
			return;

		if (tolower(text[i+m]) < pattern[m])
			left = mid + 1;
		else
			right = mid - 1;
	}
}

int main()
{
	gets(ransom);

	N = 0;
	while (true) {
		int c = getchar();
		if (c == EOF) break;

		if (isalpha(c) || c == ' ') {
			text[N++] = c;
		} else if (N != 0 && text[N-1] != '#') {
			text[N++] = '#';
		}
	}
	text[N++] = '#';

	buildSA();

	M = strlen(ransom);
	minCuts[M] = 0;

	for (int pos = M-1; pos >= 0; --pos) {
		if (ransom[pos] == ' ') {
			minCuts[pos] = minCuts[pos+1];
			continue;
		}

		int sufPos, sufLen;
		findLongestMatch(sufPos, sufLen, ransom+pos);

		while (sufLen > 0 && text[sufPos + sufLen - 1] == ' ')
			sufLen--;

		minCuts[pos] = 10000000;
		for (int len = sufLen; len >= 1; len--) {
			if (1 + minCuts[pos + len] < minCuts[pos]) {
				minCuts[pos] = 1 + minCuts[pos + len];
				cutLen[pos] = len;
				cutPos[pos] = sufPos;
			}
		}
	}

	printf("%d\n", minCuts[0]);
	for (int at = 0; at < M;) {
		if (ransom[at] == ' ') { at++; continue; }
		printf("%.*s\n", cutLen[at], text + cutPos[at]);
		at += cutLen[at];
	}
}
