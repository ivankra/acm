#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>
#include <map>
#include <gmpxx.h>
using namespace std;

typedef vector<string> VS;
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
#define all(v) (v).begin(), (v).end()
#define foreach(it,v) for(typeof((v).begin())it=(v).begin();it!=(v).end();++it)
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

vector<string> split(string s, const char *delims = " ") {
	vector<string> res;
	for (int i = 0, j; i < int(s.size()); i = j + 1) {
		j = s.find_first_of(delims, i);
		if (j == -1) j = s.size();
		if (j-i > 0) res.push_back(s.substr(i, j - i));
	}
	return res;
}

bool wins(char a, char b) {
	if (a == 'R' && b == 'S') return true;
	if (a == 'S' && b == 'P') return true;
	if (a == 'P' && b == 'R') return true;
	return false;
}

int main()
{
	for (;;) {
		int left = 0, right = 0;

		for (;;) {
			char L='-', R='-';
			if (scanf(" %c %c", &L, &R) != 2) exit(0);
			L = toupper(L);
			R = toupper(R);
			if (L == '-' && R == '-') break;
			assert(L == 'R' || L == 'P' || L == 'S');
			assert(R == 'R' || R == 'P' || R == 'S');
			if (wins(L, R)) left++;
			else if (wins(R, L)) right++;
		}
		printf("%d:%d ", left, right);
		if (left > right)
			printf("LEFT\n");
		else if (right > left)
			printf("RIGHT\n");
		else
			printf("DRAW\n");
	}
}
