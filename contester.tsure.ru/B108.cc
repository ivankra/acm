#include <cstdio>
#include <sstream>
using namespace std;

int eval(string t) {
	istringstream is(t);
	string s;
	int ret = 0;
	while (is >> s) {
		ret++;
		for (int i = 0, j = s.size()-1; i < j; i++, j--)
			if (s[i] != s[j]) { ret--; break; }
	}
	return ret;
}

int main()
{
	char s[1024], t[1024];
	gets(s); gets(t);
	int n = eval(s), m = eval(t);
	if (n < m) printf("Vasya\n");
	else if (n == m) printf("Draw\n");
	else printf("Petya\n");
}
