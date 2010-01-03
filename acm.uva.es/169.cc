#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

struct Word {
	int a, b, cnt, ok;
	bool operator <(const Word &v) const {
		if (ok != v.ok) return ok == 1;
		if (b < v.a) return true;
		if (v.b < a) return false;
		return b < v.b;
	}
};

vector<Word> words;
map<string, int> mwords;

char text[1024];
int N, here[1024], pass;

void doit(int a, int b) {
	int m = b - a + 1;
	if (m < 2 || m > 250) return;

	static char buf[256];
	memcpy(buf, text+a, m);
	buf[m] = 0;
	sort(buf, buf+m);

	string s = buf;

	if (pass == 0) {
		// pass 1: discover words and count their occurences

		if (mwords.count(s) == 0) {
			Word w = { a, b, 1, 0 };
			mwords[s] = words.size();
			words.push_back(w);
		} else {
			words[mwords[s]].cnt++;
		}
	} else {
		// pass 2: filter true words

		int w = mwords[s];
		if (words[w].cnt < 2) return;

		for (int i = a; i <= b; i++) {
			if (here[i] >= 0) {
				words[w].ok = 1;
				words[here[i]].ok = 1;
			}
			here[i] = w;
		}
	}
}

int readText() {
	char line[1024];
	for (N = 0;;) {
		if (gets(line) == NULL) return 0;

		int k = strlen(line);
		while (k > 0 && line[k-1] == '\r') line[--k] = 0;

		if (strcmp(line, "#") == 0) return 0;

		for (int i = 0; i < k; i++) {
			if (islower(line[i])) {
				assert(N <= 999);
				text[N++] = line[i];
			}
		}

		if (k == 0 || line[k-1] != '-') break;
	}
	text[N] = 0;
	return 1;
}

int main() {
	while (readText()) {
		words.clear();
		mwords.clear();

		memset(here, 0xff, sizeof(here));
		for (pass = 0; pass < 2; pass++) {
			int cn[128];

			// left spacer is a joker
			memset(cn, 0, sizeof(cn));
			for (int n = 1; n <= 250 && n < N; n++) {
				cn[text[n-1]] = 1;
				if (cn[text[n]] == 0) doit(0, n-1);
			}

			// left and right spacers are letters
			for (int a = 0; a < N; a++) {
				int b;
				for (b = a+1; b < N && b-a < 260 && text[b] != text[a]; b++);
				if (b >= N || text[b] != text[a]) continue;
				doit(a+1, b-1);
			}

			// right spacer is a joker
			memset(cn, 0, sizeof(cn));
			for (int n = 1; n <= 250 && n < N; n++) {
				cn[text[N-n]] = 1;
				if (cn[text[N-n-1]] == 0) doit(N-n, N-1);
			}
		}

		sort(words.begin(), words.end());
		for (int i = 0; i < (int)words.size(); i++)
			if (words[i].ok)
				printf("%.*s\n", words[i].b-words[i].a+1, text+words[i].a);
		printf("*\n");
	}
}
