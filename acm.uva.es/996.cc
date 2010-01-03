#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
typedef vector<int> VI;

bool isConstant(const VI &a) {
	for (int i = 1; i < (int)a.size(); i++)
		if (a[0] != a[i]) return false;
	return true;
}

string toString(int n) {
	static char buf[32];
	sprintf(buf, "%d", n);
	return string(buf);
}

pair<int, string> solve(VI a, int M)
{
	int N = a.size();
	if (isConstant(a)) return make_pair(1, "["+toString(a[0])+"]");
	if (M == 0) return make_pair(1000, string(""));

	VI b(N-1);
	for (int i = 0; i < N-1; i++) {
		b[i] = a[i+1] - a[i];
	}
	pair<int, string> tmp = solve(b, M-1);
	pair<int, string> res(tmp.first+1, "["+toString(a[0])+"+"+tmp.second+"]");
	if (res.first <= M) return res;

	b.resize(N);
	for (int i = 1; i < N; i++) {
		if (a[i-1] == 0 || a[i] % a[i-1] != 0) return res;
		b[i] = a[i] / a[i-1];
	}

	for (int d = 1; d*d <= a[0]; d++) {
		if (a[0] % d != 0) continue;
		for (int t = 0; t < 2; t++) {
			b[0] = (t == 0 ? d : (a[0]/d));
			tmp = solve(b, M-1);
			if (tmp.first+1 <= M) {
				res = make_pair(tmp.first+1, "["+toString(a[0]/b[0])+"*"+tmp.second+"]");
				return res;
			}
		}
	}

	return res;
}

int main()
{
	string line;
	while (getline(cin, line)) {
		istringstream is(line);
		VI v; int x, M;
		is >> M;
		while (is >> x) {
			v.push_back(x);
		}
		pair<int, string> s = solve(v, M);
		if (s.first > M) s.second = "[0]";
		cout << s.second << endl;
	}
}
