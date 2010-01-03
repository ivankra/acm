#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

int sim[]={0,1,5,3,4,2,9,7,8,6};

int solve(char *s) {
	int N = strlen(s);
	for (int k = N-1; k >= 0; k--) {
		int b = s[k] - '0', best = 999;
		for (int i = k; i < N; i++) {
			if (s[i]-'0' > b) best <?= s[i] - '0';
			if (sim[s[i]-'0'] > b) best <?= sim[s[i]-'0'];
		}
		if (best >= 10) continue;

		for (int i = k; i < N; i++) {
			if (s[i]-'0' == best) { swap(s[i], s[k]); break; }
			if (sim[s[i]-'0'] == best) {
				swap(s[i], s[k]);
				s[k] = '0' + sim[s[k]-'0'];
				break;
			}
		}

		for (int i = k+1; i < N; i++)
			if (sim[s[i]-'0'] < s[i]-'0') s[i] = sim[s[i]-'0'] + '0';
		sort(s+k+1, s+N);
		return 1;
	}
	return 0;
}

int main() {
	char s[256], dig[256];
	while (scanf(" %s", s) == 1 && strcmp(s, ".") != 0) {
		int k = 0;
		for (int i = 0; s[i]; i++)
			if (isdigit(s[i])) dig[k++] = s[i];
		dig[k] = 0;

		if (!solve(dig)) {
			printf("The price cannot be raised.\n");
		} else {
			k = 0;
			for (int i = 0; s[i]; i++)
				if (isdigit(s[i])) s[i] = dig[k++];
			printf("%s\n", s);
		}
	}
}
