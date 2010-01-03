#include <cstdio>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

set<string> states;

void rec(string s, int who)
{
	if (states.count(s) != 0) return;
	states.insert(s);

	for (int i = 0; i < 3; i++) {
		if (s[3*i] == 'X' && s[3*i+1] == 'X' && s[3*i+2] == 'X') return;
		if (s[3*i] == 'O' && s[3*i+1] == 'O' && s[3*i+2] == 'O') return;
		if (s[0+i] == 'X' && s[3+i] == 'X' && s[6+i] == 'X') return;
		if (s[0+i] == 'O' && s[3+i] == 'O' && s[6+i] == 'O') return;
	}

	if (s[0] == 'X' && s[4] == 'X' && s[8] == 'X') return;
	if (s[0] == 'O' && s[4] == 'O' && s[8] == 'O') return;

	if (s[2] == 'X' && s[4] == 'X' && s[6] == 'X') return;
	if (s[2] == 'O' && s[4] == 'O' && s[6] == 'O') return;

	for (int i = 0; i < 9; i++) {
		if (s[i] == '.') {
			s[i] = "XO"[who];
			rec(s, who ^ 1);
			s[i] = '.';
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	rec(".........", 0);

	for (int cs = 1; cs <= T; cs++) {
		string grid(9, ' ');
		for (int i = 0; i < 9; i++) {
			char ch;
			scanf(" %c", &ch);
			grid[i] = ch;
		}

		printf(states.count(grid) != 0 ? "yes\n" : "no\n");
	}
}
