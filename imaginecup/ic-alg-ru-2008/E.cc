#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <cassert>
using namespace std;
#define SIZE(x) int((x).size())
#define FOREACH(it, x) for(__typeof((x).begin())it=(x).begin();it!=(x).end();++it)
typedef long long LL;
typedef vector<int> VI;

char dp_str[100];
int dp_mod, dp_residue;
LL memo[20][2][20][20];

LL f(int i, int flag, int r, int ones)
{
	if (dp_str[i] == 0) {
		return (r == dp_residue && ones == 0) ? 1 : 0;
	}

	LL &res = memo[i][flag][r][ones];
	if (res != -1) return res;

	res = 0;
	for (int d = 0; d <= 9; d++) {
		if (flag && d > dp_str[i]-'0') break;
		if (d == 1 && ones == 0) continue;
		res += f(i+1, flag && (d == dp_str[i]-'0'), (r*10+d) % dp_mod, ones - (d==1?1:0));
	}
	return res;
}

LL countOnes(LL from, LL to, int residue, int modulo) {
	if (from > to || to <= 0)
		return 0;

	if (from > 0)
		return countOnes(0, to, residue, modulo) - countOnes(0, from-1, residue, modulo);

	ostringstream os;
	os << to;
	strcpy(dp_str, os.str().c_str());

	dp_mod = modulo;
	dp_residue = residue % modulo;

	memset(memo, 0xff, sizeof(memo));
	LL res = 0;
	for (int k = 1; k <= 18; k++)
		res += k * f(0, 1, 0, k);
	return res;
}

LL ten[100];
vector<pair<LL, LL> > path;
set< vector<pair<LL, LL> > > seen;
LL answer;

void go(int len, LL a, LL ones)
{
	LL b = ten[len] - 1;
	while ((b - a) % len != 0) b--;

	LL minX = a;
	for (; b >= a && b + len+1 >= ten[len]; b -= len) {
		LL o = countOnes(a, b, a % len, len);
		if (o < ones) {
			LL aa = b+len+1;
			path.push_back(make_pair(a, b));
			go(len+1, aa, ones - o);
			path.pop_back();
			continue;
		}

		LL left = (minX - a) / len, right = (b - a) / len + 1;
		while (right - left > 1) {
			LL mid = (left + right) / 2, x = a + mid * len;
			o = countOnes(a, x, a % len, len);
			if (o > ones)
				right = mid;
			else
				left = mid;
		}
		LL zb = a+len*(right-1);

		left = (minX - a) / len - 1, right = (b - a) / len;
		while (right - left > 1) {
			LL mid = (left + right) / 2, x = a + mid * len;
			o = countOnes(a, x, a % len, len);
			if (o < ones)
				left = mid;
			else
				right = mid;
		}
		LL za = a+len*(left+1);

		o = countOnes(a, za, a % len, len);
		if (o != ones) continue;

//printf("a=%lld b=%lld minX=%lld:  za=%lld zb=%lld\n", a, b, minX, za, zb);

		if (za <= zb) {
			minX = b + len;
			answer += (zb - za) / len + 1;
		}

	}
}

int main()
{
	ten[0] = 1;
	for (int n = 1; n < 100; n++) ten[n] = ten[n-1] * 10;

	int N;
	scanf("%d", &N);

	path.clear();
	answer = 0;
	go(1, 1, N);
	cout << answer << endl;
}
