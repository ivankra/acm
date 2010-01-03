#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
#include <set>
using namespace std;

int memo[256][2];

int grundy(int n, int inner) {
	int &res = memo[n][inner];
	if (res >= 0) return res;

	if (n <= 2) return res = 0;
	if (inner && n <= 4) return res = 0;

	set<int> s;
	if (inner) {
		for (int i = 2; i <= n-3; i++)
			s.insert(grundy(i, 1) ^ grundy(n-1-i, 1));
	} else {
		s.insert(grundy(n-1, 1));
		for (int i = 1; i <= n-3; i++)
			s.insert(grundy(i, 0) ^ grundy(n-1-i, 1));
	}

	res = 0;
	while (s.count(res) > 0)
		res++;
	return res;
}

bool winning(char *s) {
	if (strstr(s, "XXX") != NULL) return false;
	if (strstr(s, "XX.") != NULL) return true;
	if (strstr(s, ".XX") != NULL) return true;
	if (strstr(s, "X.X") != NULL) return true;

	int N = strlen(s);

	if (strchr(s, 'X') == NULL) {
		for (int i = 0; i < N; i++) {
			s[i] = 'X';
			if (!winning(s)) {
				s[i] = '.';
				return true;
			}
			s[i] = '.';
		}
		return false;
	}

	int g = 0;

	for (int i = 0; i < N;) {
		if (s[i] != '.') { i++; continue; }

		int inner = (i == 0) ? 0 : 1;

		int n;
		for (n = 0; i < N && s[i] == '.'; i++, n++);

		if (i == N) inner = 0;

		g ^= grundy(n, inner);
	}

	return g != 0;
}

int main()
{
	int T;
	scanf("%d", &T);

	memset(memo, 0xff, sizeof(memo));

	char s[1000];
	for (int cs = 1; cs <= T; cs++) {
		scanf(" %s", s);

		if (!winning(s)) {
			printf("LOSING\n\n");
		} else {
			printf("WINNING\n");
			for (int i = 0, k = 0; s[i]; i++) {
				if (s[i] == '.') {
					s[i] = 'X';
					if (!winning(s))
						printf(k++ ? " %d" : "%d", i+1);
					s[i] = '.';
				}
			}
			printf("\n");
		}
	}
}
