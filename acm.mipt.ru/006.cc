#include <cstdio>
#include <cstring>

int main() {
	int a[10001], n;
	scanf("%d", &n);
	memset(a, 0, sizeof(a));
	int m = n+1;
	for (int x = 0; x <= 100; x++)
		for (int y = 0; y <= 100; y++)
			for (int z = 0; z <= 100; z++)
				if (x*x+y*y+z*z <= n && a[x*x+y*y+z*z]++ == 0)
					m--;
	printf("%d\n", m);
}
