#include <cstdio>

int main()
{
	unsigned long long r=1;
	int c;
	while ((c=getchar())!=EOF)
		if ('0'<=c&&c<='9')r*=c-'0';
	printf("%llu\n", r);
}
