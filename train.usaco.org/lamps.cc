/*
ID: infnty1
PROB: lamps
LANG: C++
*/
#include <cstdio>
#include <string>
#include <set>
using namespace std;

int fin[128], n, c;

int f(int k, int m)
{
	return 1^(m&1)^((m&2)==2&&(k&1)==0)^((m&4)==4&&(k&1)==1)^((m&8)==8&&(k%3)==0);
}

int main()
{
	int i, j, x;
	set<string> R;

	freopen("lamps.in", "r", stdin);
	freopen("lamps.out", "w", stdout);

	scanf("%d %d", &n, &c);

	for (i = 0; i < n; i++) fin[i] = -1;
	while (scanf("%d", &x) == 1 && x >= 0) fin[x-1]=1;
	while (scanf("%d", &x) == 1 && x >= 0) fin[x-1]=0;

	for (x = 0; x < 16; x++) {
		for (j = 0, i = 0; i < 4; i++) j += (x >> i) & 1;
		if (j > c || (j & 1) != (c & 1)) continue;
		for (i = 0; i < n; i++) if (fin[i] >= 0 && f(i,x) != fin[i]) break;
		if (i < n) continue;
		string s = "";
		for (int i = 0; i < n; i++) s += (char)(f(i,x)+'0');
		R.insert(s);
	}

	if (R.size() == 0)
		printf("IMPOSSIBLE\n");
	else
		for (set<string>::iterator it = R.begin(); it != R.end(); it++)
			printf("%s\n", it->c_str());

	return 0;
}
