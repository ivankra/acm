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
#include <queue>
using namespace std;


int main()
{
	long long N;
	scanf("%lld", &N);

	string s = "";
	while (N != 0 || s.size() == 0) {
		int d = (N % 2 == 0 ? 0 : 1);
		s += (char)('0' + d);
		N = (N - d) / (-2);
	}

	reverse(s.begin(), s.end());
	cout << s << endl;

}
