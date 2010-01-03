#include <cstdio>
#include <cstring>
#include <cassert>

int main()
{
	int a1, an;
	while (scanf("%d %d", &a1, &an) == 2 && (a1 != 0 || an != 0)) {
		int f[100];
		memset(f, 0, sizeof(f));

		f[an] = 1;
		for (int a = an-1; a >= a1; a--) {
			f[a] = 0;
			for (int aj = a+1; aj <= an; aj++) {
				if ((aj % (aj - a)) == 0)
					f[a] += f[aj];
			}
		}
		
		printf("%d %d %d\n", a1, an, f[a1]);
	}
}
