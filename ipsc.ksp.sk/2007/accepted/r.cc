#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>
#include <map>
#include <gmpxx.h>
using namespace std;

typedef vector<string> VS;
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
#define all(v) (v).begin(), (v).end()
#define foreach(it,v) for(typeof((v).begin())it=(v).begin();it!=(v).end();++it)
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

vector<string> split(string s, const char *delims = " ") {
	vector<string> res;
	for (int i = 0, j; i < int(s.size()); i = j + 1) {
		j = s.find_first_of(delims, i);
		if (j == -1) j = s.size();
		if (j-i > 0) res.push_back(s.substr(i, j - i));
	}
	return res;
}


LL phi(LL N) {
	LL res = 1;

	for (LL p = 2; p*p <= N; p++) {
		if (N % p != 0) continue;

		res *= p-1;
		N /= p;

		while (N % p == 0) { N /= p; res *= p; }
	}

	if (N > 1) res *= N-1;

	return res;
}

mpz_class solve(LL N) {
	LL res = phi(N+1);
//	cout << "N+1=" << (N+1) << " ==> phi=" << res << endl;
	static char buf[100];
	sprintf(buf, "%lld", res);
	return mpz_class(buf);
}

int main()
{
	int T;
	cin >> T;

	for (int cs = 1; cs <= T; cs++) {
		LL N;
		cin >> N;

		mpz_class res = 0;
		for (LL div = 1; div*div <= N; div++) {
			if (N % div != 0) continue;
			res += solve(div);
			if (N/div != div) res += solve(N/div);
		}
		cout << res << endl;
	}
}
