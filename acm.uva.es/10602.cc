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

int lcp(string a, string b) {
	int k = 0;
	while (k < a.size() && k < b.size() && a[k] == b[k]) k++;
	return k;
}

int main()
{
	int T, N;
	string word[200];
	cin >> T;

	for (int cs = 1; cs <= T; cs++) {
		cin >> N;
		for (int i = 0; i < N; i++) cin >> word[i];

		vector<pair<int, string> > v;
		for (int i = 0; i < N; i++) {
			v.push_back(make_pair(-lcp(word[0], word[i]), word[i]));
		}

		sort(v.begin(), v.end());

		int cost = word[0].size();
		for (int i = 1; i < N; i++) {
			cost += word[i].size();
			cost -= lcp(v[i].second, v[i-1].second);
		}

		printf("%d\n", cost);
		for (int i = 0; i < N; i++)
			printf("%s\n", v[i].second.c_str());
	}
}
