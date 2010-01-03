#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
	char s1[256], s2[256];
	scanf(" %s %s", s1, s2);
	reverse(s1, s1+strlen(s1));
	reverse(s2, s2+strlen(s2));
	int a = atoi(s1), b = atoi(s2);
	if (a > b) swap(a, b);
	int x1=(b-a)/2, y=(a+x1)*(a+x1)-x1*x1;
	printf("%d\n%d\n",2*x1,y);
}
