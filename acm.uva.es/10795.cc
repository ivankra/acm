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

long long solve(vector<int> src, vector<int> dst)
{
	int N = src.size();
	while (N > 0 && src[N-1] == dst[N-1]) {
		src.pop_back();
		dst.pop_back();
		N--;
	}
	if (N == 0) return 0;

	bool flag = true;
	for (int i = 1; i < N; i++) flag &= (src[i] == src[0]);
	for (int i = 1; i < N; i++) flag &= (dst[i] == dst[0]);

	if (flag) {
		return (1LL << N) - 1;
	}

	int mp[4]={2,2,2,2};
	mp[src[N-1]] = 1;
	mp[dst[N-1]] = 3;

	for (int i = 0; i < N; i++) src[i] = mp[src[i]];
	for (int i = 0; i < N; i++) dst[i] = mp[dst[i]];

	vector<int> mid(N-1, 2);
	src.pop_back();
	dst.pop_back();
	return solve(src, mid) + 1 + solve(mid, dst);
}

int main()
{
	int N;
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		vector<int> a(N), b(N);
		for (int i = 0; i < N; i++) scanf("%d", &a[i]);
		for (int i = 0; i < N; i++) scanf("%d", &b[i]);
		printf("Case %d: %lld\n", cs, solve(a, b));
	}
}
