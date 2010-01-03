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
#include <queue>
#include <deque>
#include <set>
using namespace std;
typedef long long LL;

string word[32];
int N, M;

int next[512][2], final[512];
int seen[512*512*2], seenId=1, prev[512*512*2];

string trim(char *s)
{
	string res = "";
	while (*s) {
		if (*s== '0' || *s == '1')
			res += *s;
		s++;
	}
	return res;
}

string solve()
{
	for (int i = 0; i < N; i++)
		if (word[i].size() == 0) return "";

	for (int i = 0; i < N; i++)
		for (int j = i+1; j < N; j++)
			assert(word[i] != word[j]);

	memset(next, 0, sizeof(next));
	memset(final, 0, sizeof(final));
	M = 1;

	for (int i = 0; i < N; i++) {
		int x = 1;
		for (int j = 0; j < (int)word[i].size(); j++) {
			int c = word[i][j]-'0';
			if (next[x][c] == 0) {
				assert(M <= 500);
				next[x][c] = ++M;
			}
			x = next[x][c];
		}
		final[x] = 1;
	}

	int src = (1<<10)|(1<<1);
	seenId++;
	seen[src] = seenId;

	queue<int> Q;
	Q.push(src);

	while (true) {
		assert(!Q.empty());

		int s = Q.front();
		Q.pop();
		int x1 = s >> 10;
		int y1 = (s >> 1) & 511;
		int z1 = s & 1;

		if (final[x1] && final[y1] && z1) {
			string res = "";
			while (s != src) {
				res += '0' + (prev[s] & 1);
				s = prev[s] >> 1;
			}
			reverse(res.begin(), res.end());
			return res;
		}

		for (int c = 0; c <= 1; c++) {
			for (int mask = 0; mask <= 2; mask++) {
				int x2, y2, z2;
				if ((mask & 1) == 0) {
					x2 = next[x1][c];
				} else {
					if (!final[x1]) continue;
					x2 = next[1][c];
				}
				if (x2 == 0) continue;

				if ((mask & 2) == 0) {
					y2 = next[y1][c];
				} else {
					if (!final[y1]) continue;
					y2 = next[1][c];
				}
				if (y2 == 0) continue;

				z2 = z1;
				if (mask == 1 || mask == 2) z2 |= 1;

				int t = (x2 << 10) | (y2 << 1) | z2;
				if (seen[t] == seenId) continue;

				seen[t] = seenId;
				prev[t] = (s << 1) | c;
				Q.push(t);
			}
		}
	}
}

int main()
{
	char buf[1000];
	for (int cs = 1; gets(buf); cs++) {
		if (sscanf(buf, "%d", &N) != 1) break;
		if (N == 0) break;
		for (int i = 0; i < N; i++) {
			gets(buf);
			word[i] = trim(buf);
		}
		string ans = solve();
		assert(ans.size() >= 2);
		printf("Code %d: %d bits\n", cs, ans.size());
		for (int i = 0; i < (int)ans.size(); i += 20) {
			for (int j = 0; j < 20 && i + j < (int)ans.size(); j++)
				putchar(ans[i+j]);
			printf("\n");
		}
		printf("\n");
	}
}
