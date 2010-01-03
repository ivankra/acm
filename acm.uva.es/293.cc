#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <cstdlib>
#include <algorithm>
using namespace std;

int lg(int n) { for(int k=0;;k++)if((1<<k)>=n)return k; }

int type() {
	int x, y;
	char c;
	static char s[1024];

	assert(scanf(" %c", &c) == 1);

	if (c == '{') {
		int res = 0;
		while (scanf(" %[^:}] : ", s) == 1)
			res += type();
		scanf(" } ");
		return res;
	} else if (c == '(') {
		for (int n = 0;;) {
			assert(scanf(" %[^,)] %c", s, &c) == 2);
			n++;
			assert(c==',' || c==')');
			if (c == ')') return lg(n);
		}
	} else if (c == '[') {
		assert(scanf(" %d . . %d ] ", &x, &y) == 2);
		return lg(abs(x-y)+1);
	} else if (c == 'a') {
		assert(scanf(" r r a y [ %d . . %d ] o f ", &x, &y) == 2);
		return (abs(x-y)+1) * type();
	} else if (c == 's') {
		assert(scanf(" t r i n g ( %d )", &x) == 1);
		return x*7;
	}

	assert(0==1);
}

int main() {
	int T;
	scanf(" %d", &T);
	while (T-- > 0) {
		char name[1024];
		assert(scanf(" %[A-Za-z0-9_] : ", name) == 1);
		printf("A \"%s\" message requires %d bits.\n", name, type());
	}
}
