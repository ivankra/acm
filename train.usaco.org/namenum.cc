/*
ID: infnty1
PROB: namenum
LANG: C++
*/
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	char *a="ABCDEFGHIJKLMNOPRSTUVWXY";
	char s[256], t[256], w[256], map[256];

	freopen("namenum.in", "r", stdin);
	scanf(" %s", s);

	memset(map, 0, sizeof(map));
	for (int i = '2'; i <= '9'; i++) 
		map[*a++]=i, map[*a++]=i, map[*a++]=i;

	freopen("namenum.out", "w", stdout);
	freopen("dict.txt", "r", stdin);

	int k = 0;
	while (scanf(" %s", t) == 1) {
		int i;
		if (strlen(s) != strlen(t)) continue;
		for (i = 0; t[i]; i++) w[i]=map[t[i]]; w[i]=0;
		if (strcmp(w, s) == 0) k++, printf("%s\n", t);
	}

	if (k == 0) printf("NONE\n");

	return 0;
}
