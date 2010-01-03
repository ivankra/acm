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

typedef vector<string> vs;

string input;
int pos;

vs two(const string &a, const string &b) { vs r; r.push_back(a); r.push_back(b); return r; }

char rot(char c) {
	for (int i = 0; i < 4; i++)
		if ("/\\-|"[i] == c) return "\\/|-"[i];
	return c;
}

vs quilt() {
	if (input[pos] == 'A') {
		pos++;
		return two("//", "/+");
	}

	if (input[pos] == 'B') {
		pos++;
		return two("--", "--");
	}

	if (input[pos] == 't') {
		if (input[pos+1] != 'u') return vs();
		if (input[pos+2] != 'r') return vs();
		if (input[pos+3] != 'n') return vs();
		if (input[pos+4] != '(') return vs();
		pos += 5;

		vs a = quilt();
		if (a.size() == 0 || input[pos] != ')') return vs();
		pos++;

		vs b(a[0].size(), string(a.size(), ' '));
		for (int i = 0; i < a.size(); i++)
			for (int j = 0; j < a[i].size(); j++)
				b[j][a.size()-1-i] = rot(a[i][j]);
		return b;
	}

	if (input[pos] == 's') {
		if (input[pos+1] != 'e') return vs();
		if (input[pos+2] != 'w') return vs();
		if (input[pos+3] != '(') return vs();
		pos += 4;

		vs a = quilt();
		if (a.size() == 0 || input[pos] != ',') return vs();
		pos++;

		vs b = quilt();
		if (b.size() == 0 || a.size() != b.size() || input[pos] != ')') return vs();
		pos++;

		for (int i = 0; i < a.size(); i++)
			a[i] += b[i];
		return a;
	}

	return vs();
}


int main() 
{
	for (int cs = 1;; cs++) {
		input = "";
		for (;;) {
			int c = getchar();
			if (c == EOF) return 0;
			if (!isspace(c)) input += c;
			if (c == ';') break;
		}

		printf("Quilt %d:\n", cs);
		pos = 0;

		vs q = quilt();
		if (q.size() == 0) {
			printf("error\n");
		} else {
			for (int i = 0; i < q.size(); i++)
				printf("%s\n", q[i].c_str());
		}
	}
}
