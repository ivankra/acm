// ICPC Finals 2003 - Problem B - Light Bulbs
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

vector<int> readBulb()
{
	char s[200];
	scanf(" %s", s);

	int n = strlen(s);
	reverse(s, s + n);

	for (int i = 0; i < n; i++)
		s[i] -= '0';

	vector<int> v;
	while (true) {
		while (n > 0 && s[n-1] == 0) n--;
		if (n == 0) break;

		int rem = 0;
		for (int i = n-1; i >= 0; i--) {
			rem = rem * 10 + s[i];
			s[i] = rem / 2;
			rem %= 2;
		}

		v.push_back(rem);
	}

	return v;
}

void solve(vector<int> src, vector<int> dst)
{
	int N = src.size();
	vector<int> flip(N);

	if (N == 1) {
		printf(src[0] == dst[0] ? "0\n" : "1\n");
		return;
	}

	for (flip[N-1] = 0; flip[N-1] <= 1; ++flip[N-1]) {
		for (int i = N-2; i >= 0; i--) {
			int z = src[i+1] ^ (i+2 < N ? flip[i+2] : 0) ^ flip[i+1];
			if (z == dst[i+1]) {
				flip[i] = 0;
			} else {
				flip[i] = 1;
			}
		}

		int z = src[0] ^ flip[1] ^ flip[0];
		if (z == dst[0]) break;
	}

	if (flip[N-1] == 2) {
		printf("impossible\n");
		return;
	}

	char str[200];
	int len = 0;

	for (int i = N-1; i >= 0; i--) {
		int carry = flip[i];
		for (int j = 0; j < len; j++) {
			carry += str[j] * 2;
			str[j] = carry % 10;
			carry /= 10;
		}
		if (carry != 0) {
			str[len++] = carry;
		}
	}

	reverse(str, str + len);
	for (int i = 0; i < len; i++)
		str[i] += '0';
	str[len] = 0;

	printf("%s\n", str);
}


int main()
{
	for (int cs = 1; ; cs++) {
		vector<int> src = readBulb();
		vector<int> dst = readBulb();

		while (src.size() < dst.size()) src.push_back(0);
		while (dst.size() < src.size()) dst.push_back(0);
		if (src.size() == 0) break;

		if (cs > 1) printf("\n");
		printf("Case Number %d: ", cs);
		solve(src, dst);
	}
}
