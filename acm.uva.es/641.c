#include <stdio.h>
#include <string.h>

int main()
{
	static char s[1024], t[1024], u[] = "_abcdefghijklmnopqrstuvwxyz.";
	static int map[256];
	int i, k, n;

	for (i = 0; u[i]; i++)
		map[u[i]] = i;

	while (scanf("%d %s", &k, s) == 2 && k > 0) {
		for (t[n = strlen(s)] = i = 0; i < n; i++)
			t[(k * i) % n] = u[(map[s[i]] + i) % 28];
		printf("%s\n", t);
	}
	
	return 0;
}
