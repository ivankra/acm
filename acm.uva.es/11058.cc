#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
using namespace std;

char S[1024];
char tab[26];

struct Rule {
	int p, id;
	char x, y;
	bool operator <(const Rule &z) const {
		return p<z.p || (p==z.p && id < z.id);
	}
} rule[5000];
int R;

int main() {
	for (int cs = 1; scanf(" %s", S) == 1; cs++) {
		for (int i = 0; i < 26; i++)
			scanf(" %c", &tab[i]);

		scanf("%d", &R);
		for (int i = 0; i < R; i++) {
			rule[i].id = i;
			scanf("%d %c %c", &rule[i].p, &rule[i].x, &rule[i].y);
		}
//		sort(rule, rule+R);

		for (int i = 0, rp = 0; S[i]!=0; i++) {
			while (rp < R && rule[rp].p <= i) {
				tab[tolower(rule[rp].x)-'a'] =
					rule[rp].y;
				rp++;
			}

			if (isalpha(S[i]))
				S[i] = tab[tolower(S[i])-'a'];
		}

		printf("Case #%d: The encoding string is %s.\n\n", cs, S);
	}

	return 0;
}
