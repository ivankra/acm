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
using namespace std;

struct Node {
	int cost, m;
	int next[26];
} T[100100];
int TN;

int insert(const char *word) {
	int p = 0;
	for (; *word; word++) {
		int c = word[0]-'a';
		if (T[p].next[c] == 0) {
			TN++;
			T[p].next[c] = TN;
			for (int i = 0; i < 26; i++) T[TN].next[i] = 0;
			T[TN].cost = 1<<25;
		}
		p = T[p].next[c];
	}
	return p;
}

int N;
char dict[15000][32];
int dictNode[15000], dictLen[15000];
int kbd[256];

char query[300000];
int dp[300000], best[300000], bestmv[300000];

void solve() {
	int len = strlen(query);
	for (int i = 0; i < len; i++) query[i] = tolower(query[i]);

	dp[len] = 0;
	dp[len+1] = dp[len+2] = 0;

	for (int pos = len-1; pos >= 0; pos--) {
		dp[pos] = 1<<25;
		best[pos] = 1;

		for (int i = 0, p = 0; pos+i < len; i++) {
			int q = T[p].next[query[pos+i]-'a'];
			if (q == 0) break;

			int c1 = T[q].cost + 1 + dp[pos+i+1];
			if (c1 < dp[pos]) {
				dp[pos] = c1;
				best[pos] = i+1;
				bestmv[pos] = T[q].m;
			}

			p = q;
		}
	}

	if(dp[0] >= (1<<25)) { printf("\n"); return; }
	//{		for(;;)malloc(1000000);}

	int pos = 0;
	while (pos < len) {
		if (pos > 0) printf("R");

		int m = best[pos];
		for (int i = 0; i < m; i++)
			printf("%d", kbd[query[pos+i]]);

		int mv = bestmv[pos];
		if (mv > 0)
			printf("U(%d)", mv);
		else if (mv < 0)
			printf("D(%d)", -mv);
		pos += m;
	}
	printf("\n");
}

struct Rec {
	long long seq;
	int pos;

	bool operator <(const Rec &r) const {
		if (seq != r.seq) return seq < r.seq;
		return pos < r.pos;
	}
};
Rec recs[10010];

int main() {
	memset(kbd, 0, sizeof(kbd));
	for (int i = 0; i < 26; i++)
		kbd['a'+i] = kbd['A'+i] = "22233344455566677778889999"[i] - '0';

	while (scanf("%d", &N) == 1 && N > 0) {
		TN = 0;
		for (int i = 0; i < 26; i++) T[0].next[i] = 0;

		for (int i = 0; i < N; i++) {
			scanf(" %s", dict[i]);
			for (int j = 0; dict[i][j]; j++) dict[i][j] = tolower(dict[i][j]);

			dictLen[i] = strlen(dict[i]);
			dictNode[i] = insert(dict[i]);

			Rec &r = recs[i];
			r.pos = i;
			r.seq = 1;
			for (int j = 0; dict[i][j]; j++)
				r.seq = r.seq * 10LL + kbd[(int)dict[i][j]];
		}
		sort(recs, recs+N);
		recs[N].seq = -1;

		for (int i = 0, j; i < N; i = j) {
			for (j = i; j < N && recs[j].seq == recs[i].seq; j++);

			for (int k = i; k < j; k++) {
				int w = recs[k].pos;
				T[dictNode[w]].cost = dictLen[w] + min(k-i, j-k);
				T[dictNode[w]].m = (k-i) < (j-k) ? (k-i) : -(j-k);
				//printf("cost of %s: %d\n", dict[w], T[dictNode[w]].cost);
			}
		}

		int Q;
		scanf("%d", &Q);

		while (Q-- > 0 && scanf(" %s", query) == 1) {
			solve();
		}
	}
}
