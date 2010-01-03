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


int main()
{
	int T;
	cin >> T;

	for (int cs = 1; cs <= T; cs++) {

	}
}
