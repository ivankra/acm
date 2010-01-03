#include <iostream>
using namespace std;

string s;
int p;

void expr();

void factor() {
	if (s[p] == '(') {
		p++;
		expr();
		if (s[p] == ')') p++;
	} else if (s[p] != '$') {
		cout << s[p++];
	}
}

void term() {
	factor();
	while (s[p] == '*' || s[p] == '/') {
		char c = s[p++];
		factor();
		cout << c;
	}
}


void expr() {
	term();
	while (s[p] == '+' || s[p] == '-') {
		char c = s[p++];
		term();
		cout << c;
	}
}

int main() {
	cin >> s;
	s += "$";
	p = 0;
	expr();
	cout << endl;
}
