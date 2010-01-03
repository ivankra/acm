#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	char s[1024];
	scanf(" %s", s);
	if (next_permutation(s, s+strlen(s)))
		printf("%s\n", s);
	else
		printf("no word\n");
}
