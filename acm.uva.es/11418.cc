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
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
#define FOREACH(it, v) for(typeof((v).begin())it=(v).begin();it!=(v).end();++it)
#define SIZE(v) ((int)(v).size())
#define ALL(v) (v).begin(), (v).end()
#define REP(i,n) for(int i=0;i<(n);++i)

int N, match[50], seen[50];
char *xmatch[50], *name[50][50];

int dfs(int x) {
	if (seen[x]++) return 0;
	for (int i = 0; i < N; i++) {
		if (name[i][x] == NULL) continue;
		if (match[i] == -1 || dfs(match[i])) {
			match[i] = x;
			xmatch[x] = name[i][x];
			return 1;
		}
	}
	return 0;
}

int main()
{
	int T; char buf[1000];
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		memset(name, 0, sizeof(name));
		for (int i = 0; i < N; i++) {
			int K;
			scanf("%d", &K);
			for (int j = 0; j < K; j++) {
				scanf(" %s", buf);
				buf[0] = toupper(buf[0]);
				for (int t = 1; buf[t]; t++) buf[t] = tolower(buf[t]);
				name[i][toupper(buf[0])-'A'] = strdup(buf);
			}
		}

		memset(match, 0xff, sizeof(match));
		memset(xmatch, 0, sizeof(xmatch));
		for (int i = 0; i < N; i++) {
			memset(seen, 0, sizeof(seen));
			if (!dfs(i)) assert(0==1);
		}

		printf("Case #%d:\n", cs);
		for (int i = 0; i < N; i++) {
			printf("%s\n", xmatch[i]);
		}

	}
}
