#include <cstdio>
#include <cstring>
#include <cassert>
#include <string>
#include <algorithm>
using namespace std;
typedef unsigned long long u64;

int cnt[32], m;
u64 fact[128];

u64 count_perm() {
	int n = 0;
	for (int i = 0; i < 26; i++) n += cnt[i];

	u64 r = fact[n];
	for (int i = 0; i < 26; i++) r /= fact[cnt[i]];
	return r;
}

int solve() {
	int odd = -1;
	for (int i = 0; i < 26; i++) {
		if ((cnt[i] % 2) != 1) continue;
		if (odd >= 0) return 1;
		odd = i;
	}

	if (odd >= 0) cnt[odd]--;
	for (int i = 0; i < 26; i++) cnt[i] /= 2;

	u64 total = count_perm();
	if (m < 1 || m > total) return 1;

	string lex = "";
	m--;

	int k = 0;
	for (int i = 0; i < 26; i++) k += cnt[i];

	while (k-- > 0) {
		for (int c = 0; c < 26; c++) {
			if (cnt[c] <= 0) continue;
			cnt[c]--;
			u64 x = count_perm();
			if (m >= x) {
				m -= x;
				cnt[c]++;
			} else {
				lex += (char)(c+'a');
				break;
			}
		}
	}

	printf("%s", lex.c_str());
	if (odd >= 0) putchar(odd+'a');
	for (int i = lex.size()-1; i >= 0; i--) putchar(lex[i]);
	printf("\n");

	return 0;
}

int main() {
	fact[0] = 1;
	for (int n = 1; n < 128; n++)
		fact[n] = fact[n-1] * (u64)n;

	int T;
	char s[256];
	scanf("%d", &T);
	for (int cs = 1; cs <= T && scanf(" %s %d", s, &m) == 2; cs++) {
		printf("Case %d: ", cs);

		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; s[i]; i++) {
			assert('a' <= s[i] && s[i] <= 'z');
			cnt[s[i] - 'a']++;
		}

		if (solve()) printf("XXX\n");
	}
}
