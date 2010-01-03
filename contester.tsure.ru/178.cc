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
using namespace std;

string add(string a, int k, string b) {
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	int carry = 0;
	string res = "";

	for (int i = 0; i < (int)max(a.size(), b.size())+3; i++) {
		if (i < (int)a.size()) carry += a[i] - '0';
		if (i < (int)b.size()) carry += k * (b[i] - '0');

		int digit = (carry % 10 + 10) % 10;
		res += digit + '0';

		carry = (carry - digit) / 10;
	}

	assert(carry == 0);
	while (res.size() > 1 && res[res.size()-1] == '0') res.resize(res.size()-1);

	reverse(res.begin(), res.end());
	return res;
}

string mul(string a, string b) {
	string res = "0";
	for (int i = b.size()-1; i >= 0; i--) {
		res = add(res, b[i]-'0', a);
		a += '0';
	}
	return res;
}

string div2(string a) {
	int c = 0;
	for (int i = 0; i < (int)a.size(); i++) {
		c = c * 10 + a[i] - '0';
		a[i] = '0' + (c / 2);
		c %= 2;
	}

	while (a.size() > 0 && a[0] == '0') a = a.substr(1);
	return a;
}

int main() {
	string N, Q, K;
	cin >> N >> Q >> K;
	cout << add(div2(mul(N, add(N, 1, "1"))), -1, K) << endl;
}
