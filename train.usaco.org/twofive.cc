/*
ID: infnty1
TASK: twofive
LANG: C++
*/
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

char partial[8][8];
bool fixedByPartial[25];

long long memo[6][6][6][6][6];

long long f(int a1, int a2, int a3, int a4, int a5) {
	long long &res = memo[a1][a2][a3][a4][a5];
	if (res != -1) return res;

	int a[]={a1,a2,a3,a4,a5}, n=a1+a2+a3+a4+a5;

	// The first n letters of the alphabet have been already
	// placed on the board, in the top a[i] cells of i-th column.
	// a1 >= a2 >= ... >= a5.

	if (n == 25) return res = 1;

	// Now we're looking for possible ways to place (n+1)st letter.
	res = 0;
	for (int x = 0; x < 5; x++) {
		int y = a[x];	// Next letter must be placed exactly below the last letter of some column

		if (x > 0 && a[x]+1 > a[x-1])
			// Placing a letter here would leave a gap on y-th row
			continue;

		if (fixedByPartial[n]) {
			if (partial[y][x] != 'A'+n) continue;
		} else {
			if (partial[y][x] != '.') continue;
		}

		a[x]++;
		res += f(a[0], a[1], a[2], a[3], a[4]);
		a[x]--;
	}

	return res;
}

// Returns number of solutions which begins with string s.
long long complete(const char *s) {
	for (int i = 0; s[i]; i++)
		for (int j = 0; j < i; j++)
			if (s[i] == s[j]) return 0;

	memset(partial, '.', sizeof(partial));
	memset(fixedByPartial, 0, sizeof(fixedByPartial));
	for (int i = 0; s[i]; i++) {
		partial[i/5][i%5] = s[i];
		fixedByPartial[s[i]-'A'] = true;
	}

	memset(memo, 0xff, sizeof(memo));
	return f(0, 0, 0, 0, 0);
}

long long complete(const string &s) { return complete(s.c_str()); }

int main()
{
	freopen("twofive.in", "r", stdin);
	freopen("twofive.out", "w", stdout);

	char op;
	scanf(" %c", &op);

	if (op == 'N') {
		long long n;
		scanf("%lld", &n);
		n--;

		string s = "A";
		while (s.size() != 25) {
			char c;
			for (c = 'A'; c < 'Z'; c++) {
				long long t = complete(s+c);
				if (n >= t) n -= t; else break;
			}
			s += c;
		}
		printf("%s\n", s.c_str());
	} else if (op == 'W') {
		char buf[256];
		scanf(" %s", buf);

		string s(buf);
		long long n = 0;

		for (int i = 0; i < 24; i++)
			for (char c = 'A'; c < s[i]; c++)
				n += complete(s.substr(0, i) + c);

		printf("%lld\n", n+1);
	}
}
