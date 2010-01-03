#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

bool eq(string s, string t) {
	if (s.size() != t.size()) return false;
	for (int i = 0; i < (int)s.size(); i++)
		if (tolower(s[i]) != tolower(t[i])) return false;
	return true;
}

int main() {
	char buf[1024];
	int N;

	for (int cs = 1; gets(buf) && sscanf(buf, "%d", &N) == 1 && N > 0; cs++) {
		vector<string> stk;

		printf("Test Case %d\n", cs);
		int L = 1, err = 0;
		while (L <= N) {
			int c = getchar();
			if (c == '\n') { L++; continue; }
			if (err || c != '<') continue;

			c = getchar();

			int open = 1;
			if (c == '/') { open = 0; c = getchar(); }

			string tag = "";

			while (c != '>') {
				if (!isupper(c)) {
					printf("line %d: bad character in tag name.\n", L);
					err = 1;
					ungetc(c, stdin);
					break;
				}
				if (tag.size() >= 10) {
					printf("line %d: too many/few characters in tag name.\n", L);
					err = 1;
					ungetc(c, stdin);
					break;
				}
				tag += (char)c;
				c = getchar();
			}
			if (err) continue;

			if (tag.size() < 1) {
				printf("line %d: too many/few characters in tag name.\n", L);
				err = 1;
				continue;
			}

			if (open) {
				stk.push_back(tag);
				continue;
			}

			if (stk.size() == 0) {
				printf("line %d: no matching begin tag.\n", L);
				err = 1;
				continue;
			}

			if (!eq(stk.back(), tag)) {
				printf("line %d: expected </%s>\n", L, stk.back().c_str());
				err = 1;
				continue;
			}

			stk.pop_back();
		}

		if (!err && stk.size() != 0) {
			printf("line %d: expected </%s>\n", N, stk.back().c_str());
			err = 1;
		}

		if (!err) printf("OK\n");
	}
}
