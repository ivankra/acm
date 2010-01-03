#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

char digs[100];
int op[100], N;
long long num[100];
vector<string> out;

void go(int m, int dp, long long pval, long long mval) {
	if (dp >= N) {
		if (m==1 || pval+mval != 2000LL) return;

		static char s[100];
		sprintf(s, "%lld", num[0]);
		for (int i = 1; i < m; i++)
			sprintf(s+strlen(s), "%c%lld", op[i], num[i]);
		out.push_back(string(s));

		return;
	}

	num[m] = 0;
	for (int i = 1; dp+i <= N; i++) {
		if (i > 1 && digs[dp]=='0') break;
		num[m] = num[m] * 10 + (digs[dp+i-1] - '0');

		op[m] = '+';
		go(m+1, dp+i, pval+mval, num[m]);

		op[m] = '-';
		go(m+1, dp+i, pval+mval, -num[m]);

		op[m] = '*';
		go(m+1, dp+i, pval, mval*num[m]);
	}
}

int main() {
	for (int cs = 1; scanf(" %[0-9] =", digs) == 1; cs++) {
		printf("Problem %d\n", cs);
		out.clear();

		N = strlen(digs);

		num[0] = 0;
		for (int i = 1; i <= N; i++) {
			if (i>1 && digs[0]=='0') break;
			num[0] = num[0] * 10 + (digs[i-1] - '0');
			go(1,i,0,num[0]);
		}

		sort(out.begin(), out.end());
		for (int i = 0; i < (int)out.size(); i++)
			printf("  %s=\n", out[i].c_str());
		if (out.size() == 0)
			printf("  IMPOSSIBLE\n");
	}
}
