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
typedef long long LL;

#define MOD 10007

struct Node {
	Node *next[5];
	bool fin;
	short buf[201];

	Node() {
		memset(next, 0, sizeof(next));
		fin = false;
	}

	~Node() {
		for (int i = 0; i < 5; i++)
			if (next[i] != NULL) delete next[i];
	}
};

int K, M;
short dp_full_buf[10][1000];
short *dp_full[10], dp_one[1000]={1};

int dfs(Node *root)
{
	if (root->fin) return 0;

	int res = 0;
	root->fin = 1;
	for (int i = 0; i < K; i++) {
		if (root->next[i] == NULL) {
			res++;
			root->fin = 0;
		} else {
			res += dfs(root->next[i]);
			if (!root->next[i]->fin) root->fin = 0;
		}
	}
	return res;
}

short *eval(Node *root)
{
	if (root == NULL) return dp_full[K];
	if (root->fin) return dp_one;

	short *sub[5];
	for (int i = 0; i < K; i++)
		sub[i] = eval(root->next[i]);

	short dp[201], dp_next[201];
	memset(dp, 0, sizeof(dp[0]) * (M+1));
	dp[0] = 1;

	for (int k = 0; k < K; k++) {
		memset(dp_next, 0, sizeof(dp_next[0]) * (M+1));
		for (int a = 0; a <= M; a++) {
			if (dp[a] == 0) continue;
			for (int b = 0; a+b <= M; b++)
				dp_next[a+b] = (dp_next[a+b] + dp[a] * (int)sub[k][b]) % MOD;
		}
		memcpy(dp, dp_next, sizeof(dp[0]) * (M+1));
	}

	memcpy(root->buf, dp, sizeof(dp[0]) * (M+1));
	return root->buf;
}

int solve(Node *root)
{
	if (dp_full[K] == NULL) {
		short *z = dp_full_buf[K];
		dp_full[K] = z;
		z[0] = 0;
		z[1] = 1;
		for (int m = 2; m <= 200; m++) {
			int dp[6][201];
			memset(dp, 0, sizeof(dp));
			dp[0][0] = 1;
			for (int k = 1; k <= K; k++)
				for (int i = 0; i <= m; i++)
					for (int j = 1; i+j <= m; j++)
						dp[k][i+j] = (dp[k][i+j] + dp[k-1][i] * (int)z[j]) % MOD;
			z[m] = dp[K][m];
		}
	}

	int k = dfs(root);
	if (k > M) return 0;

	return eval(root)[M];
}

int main()
{
	int T, N;
	char str[10000];

	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &N, &M, &K);

		Node *root = new Node();
		for (int i = 0; i < N; i++) {
			scanf(" %s", str);
			Node *p = root;
			for (int j = 0; str[j]; j++) {
				int d = str[j] - '0';
				if (p->next[d] == NULL)
					p->next[d] = new Node();
				p = p->next[d];
			}
			p->fin = true;
		}

		printf("%d\n", solve(root));
		delete root;
	}
}
