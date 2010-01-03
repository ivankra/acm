#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <ctime>
using namespace std;

typedef long long LL;

LL memo[310][11][8][8];

LL rec(int frame, int bonus1, int bonus2, int score)
{
	if (score < 0) return 0;

	LL &res = memo[score][frame][bonus1][bonus2];
	if (res != -1) return res;

	if (frame == 10) {
		res = 0;

		if (bonus1 == 0) {
			if (score == 0) return res = 1;
		} else if (bonus2 == 0) {
			for (int n = 0; n <= 10; n++)
				if (score == bonus1*n) res++;
		} else {
			for (int n = 0; n <= 10; n++) {
				for (int m = 0; m <= 10; m++) {
					if (n != 10 && n+m > 10) continue;
					if (score == bonus1*n + bonus2*m) res++;
				}
			}
		}

		return res;
	}

	res = 0;

	for (int n = 0; n < 10; n++) {
		for (int m = 0; n+m <= 10; m++) {
			int s = score - n - m;
			s -= bonus1 * n;
			s -= bonus2 * m;
			res += rec(frame+1, (n+m==10)?1:0, 0, s);
		}
	}

	if (bonus1 == 0) {
		res += rec(frame+1, 1, 1, score-10);
	} else if (bonus2 == 0) {
		res += rec(frame+1, bonus2+1, 1, score-10-bonus1*10);
	} else {
		res += rec(frame+1, bonus2+1, 1, score-10-bonus1*10);
	}

	return res;
}

int main()
{
	int n;
	memset(memo, 0xff, sizeof(memo));
	while (scanf("%d", &n) == 1 && n >= 0)
		printf("%lld\n", rec(0, 0, 0, n));
	return 0;
}
