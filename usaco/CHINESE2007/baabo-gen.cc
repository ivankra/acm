#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	int N = 1000;
	printf("%d\n", N);
	srand(time(NULL));
	for (int i = 0; i < 2*N; i++) printf("%d\n", rand() % 1000);
}
