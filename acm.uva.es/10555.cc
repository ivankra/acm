#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>
#include <map>
using namespace std;


int main()
{
	string s;
	while (cin >> s && s != "0") {
		s = s.substr(2, s.size() - 5);
		int n = s.size();
		long long bestP = 0, bestQ = LLONG_MAX, ten[100];

		ten[0] = 1;
		for (int i = 1; i < 30; i++) ten[i] = ten[i-1] * 10LL;

		for (int p = 1; p <= n; p++) {
			long long a = 0, b = 0;
			for (int i = 0; i < n-p; i++) a = a * 10 + s[i]-'0';
			for (int i = n-p; i < n; i++) b = b * 10 + s[i]-'0';

			long long pp = a * (ten[p] - 1) + b;
			long long qq = ten[n-p] * (ten[p] - 1);
			long long g = __gcd(pp, qq); pp /= g; qq /= g;
			if (qq < bestQ) { bestP = pp; bestQ = qq; }
		}

		cout << bestP << "/" << bestQ << "\n";


	}
}
