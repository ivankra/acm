#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

bool ls(const string &a, const string &b) {
	return a.size() < b.size() || (a.size() == b.size() && a < b);
}

bool leq(const string &a, const string &b) {
	return a.size() < b.size() || (a.size() == b.size() && a <= b);
}

string sub(string a, string b) {
	if (a == b) return "0";
	assert(ls(b, a));

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	string res;
	for (int i = 0, c = 0; i < (int)a.size(); i++) {
		c += a[i]-'0' - (i < (int)b.size() ? b[i]-'0' : 0);
		if (c < 0) {
			res += c+10+'0';
			c = -1;
		} else {
			res += c+'0';
			c = 0;
		}
	}

	while (res.size() > 1 && res[res.size()-1] == '0')
		res.resize(res.size()-1);
	reverse(res.begin(), res.end());
	return res;
}

void div(const string &num, string den, string &q, string &r) {
	int k = 0;

	q = "";
	r = num;

	while (leq(den, r)) {
		k++;
		den += "0";
	}

	if (k == 0) {
		q = "0";
		r = num;
		return;
	}

	while (k-- > 0) {
		den.resize(den.size()-1);

		int z = 0;
		while (leq(den, r)) {
			r = sub(r, den);
			z++;
		}

		q += (char)(z+'0');
	}
}

int main() 
{
	string p, q;
	for (int cs = 1; cin >> p >> q; cs++) {
		if (p[0] == '0' || q[0] == '0') break;

		cout << "Case " << cs << ":" << endl;
		cout << p << " / " << q << endl;

		vector<string> a;
		for (;;) {
			string t, rem;
			div(p, q, t, rem);
			p = rem;

			if (p == "0") {
				a.push_back(sub(t, "1"));
				a.push_back("1");
				break;
			} else {
				a.push_back(t);
				swap(p, q);
			}
		}

		int n = a.size();

		int W = 3 * (n-1);
		for (int i = 0; i < n; i++)
			W += a[i].size();

		int sh = 0;
		for (int i = 0; i < n-1; i++) {
			int sh1 = sh + a[i].size() + 3;

			int m = max(0, (W-sh1-1)/2);
			cout << string(sh1+m, '.') << '1' << string(max(0,W-sh1-m-1), '.') << endl;
			cout << string(sh, '.') << a[i] << ".+." << string(max(0,W-sh1), '-') << endl;

			sh = sh1;
		}

		cout << string(W-1, '.') << '1' << endl;
	}
}
