#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

int inversions(string s, string t)
{
	int n = s.size();
	vector<int> v;
	for (int i = 0; i < n; i++) {
		for (int j = 0;; j++) {
			assert(j < n);
			if (s[i] == t[j]) {
				t[j] = ' ';
				v.push_back(j);
				break;
			}
		}
	}

	int res = 0;
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			if (v[i] > v[j]) res++;
	return res;
}

int solve(char *s)
{
	int n = strlen(s);

	vector<int> cnt(26, 0);
	for (int i = 0; i < n; i++) {
		assert(islower(s[i]));
		++cnt[s[i]-'a'];
	}

	int odd = -1;
	for (int i = 0; i < 26; i++) {
		if (cnt[i] % 2 != 0) {
			if (odd != -1) return -1;
			odd = i;
		}
	}
	cnt[odd]--;

	string left, right;
	vector<int> c(26, 0);
	for (int i = 0; i < n; i++) {
		if (++c[s[i]-'a'] <= cnt[s[i]-'a']/2)
			left += s[i];
	}

	c.assign(26, 0);
	for (int i = n-1; i >= 0; i--)
		if (++c[s[i]-'a'] <= cnt[s[i]-'a']/2)
			right = s[i] + right;

	string t;
	if (odd < 0)
		t = left + right;
	else
		t = left + (char)('a'+odd) + right;

	int res = inversions(s, t);
	reverse(right.begin(), right.end());
	res += inversions(left, right);
	return res;
}

int main()
{
	char s[1000];
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf(" %s", s);
		int res = solve(s);
		if (res < 0)
			printf("Impossible\n");
		else
			printf("%d\n", res);
	}
}
