#include <stdio.h>
#include <ctype.h>
#include <set>
#include <string>
using namespace std;

int main()
{
	set<string> s;
	char w[1024];

	for (int n = 0;;) {
		int c = getchar();
		if (isalpha(c)) w[n++] = tolower(c);
		else if (n > 0) { w[n]=0; s.insert(w); n=0; }
		if (c == EOF) break;
	}

	for (set<string>::iterator it = s.begin(); it != s.end(); it++)
		printf("%s\n", it->c_str());

	return 0;
}
