#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

string s;
int k, x;

bool eval() {
	char c = s[k++];

	if (islower(c))
		return (x & (1 << (c-'p'))) != 0;

	if (c == 'N')
		return !eval();

	bool x = eval();
	bool y = eval();

	if (c == 'K') return x & y;
	if (c == 'A') return x | y;
	if (c == 'C') return x || y == 0;
	return x == y;
}

int main() {
	while (cin >> s && s != "0") {
		bool t = true;
		for (x = 0; t && x < 32; x++) {
			k = 0;
			t &= eval();
		}
		printf(t ? "tautology\n" : "not\n");
	}
}
