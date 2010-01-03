#include <cstdio>
#include <cctype>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<string, int> foo; string bar[8];
int who(const string &x) {
	if (foo.count(x) == 0) {
		int y = foo.size();
		foo[x] = y;
		bar[y] = x;
	}
	return foo[x];
}

int main()
{
	vector<int> out;
	string A, B, s;

	int holds[8];
	memset(holds, 0xff, sizeof(holds));
	foo.clear();

	while (cin >> A >> s) {
		if (A == "No" || A == "no") break;
		int a = who(A);
		if (s == "take") {
			cin >> s >> s;
			holds[a] = out.size();
			out.push_back(0);
		} else if (s == "eat") {
			cin >> s >> s;
			out[holds[a]] = a;
			holds[a] = -1;
		} else {
			cin >> s >> B;
			swap(holds[a], holds[who(B)]);
		}
	}

	for (; out.size() != 0; out.pop_back())
		printf("%s\n", bar[out.back()].c_str());
}
