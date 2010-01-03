#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

vector<int> A, B;
map<int, int> memo;

int f(int i, int j, int last) {
	int key = (last + 1)*5000LL + i*60 + j;
	if (memo.count(key) > 0) return memo[key];

	int &res = memo[key];
	res = 0;

	if (i < A.size()) res >?= (last>=0 ? abs(last-A[i]) : 0) + f(i+1, j, A[i]);
	if (j < B.size()) res >?= (last>=0 ? abs(last-B[j]) : 0) + f(i, j+1, B[j]);
	return res;
}

int main()
{
	int T, N;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N); cs++) {
		vector<int> v(N, 0);
		for (int i = 0; i < N; i++) scanf("%d", &v[i]);
		sort(v.begin(), v.end());

		int res = 0;
		for (int k = -2; k <= 2; k++) {
			A.clear(); B.clear();
			for (int i = 0; i < N; i++) {
				if (i >= N/2+k) A.push_back(v[i]);
				else B.push_back(v[i]);
			}

			memo.clear();
			res >?= f(0, 0, -1);
		}

		printf("Case %d: %d\n", cs, res);
	}
}
