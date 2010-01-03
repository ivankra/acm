/*
ID: infnty1
PROB: lgame
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

char buf[256], dict[5100][8];
int val[256], N, dictv[5100], dictc[5100][8];
int lmax[256], lm[26], let[26], L;

static inline bool can(int i, int j) {
	for (int k = 0; k < L; k++)
		if (dictc[i][k] + dictc[j][k] > lm[k]) return false;
	return true;
}

int main() {
	for (int i = 0; i < 26; i++) {
		char *a = "qwertyuiopasdfghjklzxcvbnm";
		char *b = "76122541352146557637746525";
		val[(int)a[i]] = b[i] - '0';
	}

	freopen("lgame.in", "r", stdin);
	scanf(" %s", buf);

	L = 0;
	for (int c = 'a'; c <= 'z'; c++) {
		lmax[c] = 0;
		for (int i = 0; buf[i]; i++)
			if (buf[i] == c) lmax[c]++;
		if (lmax[c] > 0) {
			lm[L] = lmax[c];
			let[L++] = c;
		}
	}

	freopen("lgame.dict", "r", stdin);
	while (scanf(" %s", buf) == 1 && buf[0] != '.') {
		int cnt[256], ok = 1;

		for (int c = 'a'; ok && c <= 'z'; c++) {
			cnt[c] = 0;
			for (int i = 0; buf[i]; i++)
				if (buf[i] == c) cnt[c]++;
			if (cnt[c] > lmax[c]) ok = 0;
		}
		if (!ok) continue;

		strcpy(dict[N], buf);

		dictv[N] = 0;
		for (int i = 0; buf[i]; i++)
			dictv[N] += val[(int)buf[i]];

		for (int i = 0; i < L; i++)
			dictc[N][i] = cnt[let[i]];

		N++;
	}

	int maxv = 0;
	for (int i = 0; i < N; i++) {
		maxv >?= dictv[i];
		for (int j = i; j < N; j++)
			if (can(i,j)) maxv >?= dictv[i] + dictv[j];
	}

	freopen("lgame.out", "w", stdout);
	printf("%d\n", maxv);
	for (int i = 0; i < N; i++) {
		if (dictv[i] == maxv) printf("%s\n", dict[i]);
		for (int j = i; j < N; j++)
			if (dictv[i] + dictv[j] == maxv && can(i,j))
				printf("%s %s\n", dict[i], dict[j]);
	}
}
