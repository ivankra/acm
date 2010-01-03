// ACM ICPC World Finals 2007
// Problem A+. Consanguine Calculations.
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

enum { A=1, B=2, AB=4, O=8};
int tab[4][4] = {
        /*       A         B       AB     O */
/*A*/   {      A|O, A|B|AB|O,  A|B|AB,  A|O },
/*B*/   { A|B|AB|O,      B|O,  A|B|AB,  B|O },
/*AB*/  {   A|B|AB,   A|B|AB,  A|B|AB,  A|B },
/*O*/   {      A|O,      B|O,     A|B,    O }
};

int index(const string &s) {
	if (s == "A") return 0;
	if (s == "B") return 1;
	if (s == "AB") return 2;
	return 3;
}

bool valid(string p, string q, string c) {
	if (c[c.size()-1] == '+' && p[p.size()-1] == '-' && q[q.size()-1] == '-') return false;
	p.resize(p.size()-1); q.resize(q.size()-1); c.resize(c.size()-1);

	return (tab[index(p)][index(q)] & (1 << index(c))) != 0;
}

string bloods[] = { "A+", "A-", "AB+", "AB-", "B+", "B-", "O+", "O-" };
vector<string> oneParent(string p, string c) {
	vector<string> res;
	for (int i = 0; i < 8; i++)
		if (valid(p, bloods[i], c)) res.push_back(bloods[i]);
	return res;
}

vector<string> twoParents(string p, string q) {
	vector<string> res;
	for (int i = 0; i < 8; i++)
		if (valid(p, q, bloods[i])) res.push_back(bloods[i]);
	return res;
}

ostream &operator <<(ostream &o, const vector<string> &v) {
	if (v.size() == 0) {
		o << "IMPOSSIBLE";
	} else if (v.size() == 1) {
		o << v[0];
	} else {
		for (int i = 0; i < (int)v.size(); i++)
			o << (i == 0 ? "{" : ", ") << v[i];
		o << "}";
	}
	return o;
}

int main()
{
	string p1, p2, ch;
	for (int cs = 1; cin >> p1 >> p2 >> ch; cs++) {
		if (p1 == "E") break;

		cout << "Case " << cs << ":";
		if (p1 == "?")
			cout << " " << oneParent(p2, ch) << " " << p2 << " " << ch << endl;
		else if (p2 == "?")
			cout << " " << p1 << " " << oneParent(p1, ch) << " " << ch << endl;
		else
			cout << " " << p1 << " " << p2 << " " << twoParents(p1, p2) << endl;
	}
}
