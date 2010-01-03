#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n, a[1010];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a, a+n);
	printf("%d\n", a[(n-1)/2]);
}
