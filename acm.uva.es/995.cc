#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int mod(const string &s, int base, int y) {
	int res = 0;
	for (int i = 0; i < (int)s.size(); i++)
		res = (res * base + s[i] - '0') % y;
	return res;
}

int main()
{
	int B, K;
	char digits[100];

	while (scanf("%d %s", &B, digits) == 2 && B > 0) {
		vector<string> super[100];

		K = strlen(digits);
		sort(digits, digits+K);

		for (int i = 0; i < K; i++) {
			if (i != 0 && digits[i-1] == digits[i]) continue;
			if (digits[i] == '0') continue;
			super[1].push_back(string(1, digits[i]));
		}

		int m = 1;
		while (true) {
			for (int w = 0; w < super[m].size(); w++) {
				for (int i = 0; i < K; i++) {
					if (i != 0 && digits[i-1] == digits[i]) continue;
					string s = super[m][w] + digits[i];
					if (mod(s, B, m+1) == 0) {
						super[m+1].push_back(s);
					}
				}
			}

			if (super[m+1].size() == 0) break;
			m++;
		}
		
		printf("%s\n", super[m].back().c_str());
	}

	return 0;
}
