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

long long ans[210000];

int main()
{
	ans[0] = 0;
	for (int n = 1; n <= 500; n++) {
		ans[n] = ans[n-1];
		for (int i = 1; i < n; i++)
			ans[n] += __gcd(i, n);
	}

	int N;
	while (cin >> N && N > 0)
		cout << ans[N] << "\n";
}
