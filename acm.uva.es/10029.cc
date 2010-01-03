#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

int N, dp[26000];
char dict[26000][20];

enum { HDIV = 533879 };
int hnext[26000], hword[26000], htab[HDIV], hsize=0;

int lookup(const char *s, int add = -1) {
	int hash = 0;
	for (int i = 0; s[i]; i++) {
		hash = hash * 31 + s[i] - 'a';
		if (hash >= HDIV) hash %= HDIV;
	}

	for (int i = htab[hash]; i != 0; i = hnext[i])
		if (strcmp(s, dict[hword[i]]) == 0) return hword[i];

	if (add >= 0) {
		hsize++;
		hword[hsize] = add;
		hnext[hsize] = htab[hash];
		htab[hash] = hsize;
		return hsize;
	}

	return -1;
}

int main() {
	N = 0;
	while (scanf(" %s", dict[N]) == 1) N++;

	int best = 0;
	for (int i = N-1; i >= 0; i--) {
		int m = strlen(dict[i]), t;
		char s[50];

		dp[i] = 1;

		// change letter
		strcpy(s, dict[i]);
		for (int j = 0; j < m; j++) {
			for (int ch = 'a'; ch <= 'z'; ch++) {
				if (ch == dict[i][j]) continue;
				s[j] = ch;
				if ((t = lookup(s)) > i) dp[i] >?= 1 + dp[t];
			}
			s[j] = dict[i][j];
		}

		// insert letter
		for (int j = 0; m <= 15 && j <= m; j++) {
			for (int k = 0; k < j; k++) s[k] = dict[i][k];
			for (int ch = 'a'; ch <= 'z'; ch++) {
				s[j] = ch;
				for (int k = j; k < m; k++) s[k+1] = dict[i][k];
				s[m+1] = 0;
				if ((t = lookup(s)) > i) dp[i] >?= 1 + dp[t];
			}
		}

		// erase letter
		if (m > 1) {
			for (int j = 0; j < m; j++) {
				strcpy(s, dict[i]);
				for (int k = j+1; k <= m; k++) s[k-1] = s[k];
				if ((t = lookup(s)) > i) dp[i] >?= 1 + dp[t];
			}
		}

		best >?= dp[i];

		lookup(dict[i], i);
	}

	printf("%d\n", best);	
}
