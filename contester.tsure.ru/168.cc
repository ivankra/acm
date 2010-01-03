#include <iostream>
using namespace std;

int main()
{
	long long n, x, y, res=0;
	cin >> n >> x >> y;

	res += min(n-x, n-y);
	res += min(n-x, y-1);
	res += min(x-1, n-y);
	res += min(x-1, y-1);

	for (int dx = -2; dx <= 2; dx++) {
		for (int dy = -2; dy <= 2; dy++) {
			if ((abs(dx)==1 && abs(dy)==2) || (abs(dx)==2 && abs(dy)==1)) {
				if (1 <= x+dx && x+dx <= n && 1 <= y+dy && y+dy <= n)
					res++;
			}
		}
	}

	cout << res << endl;
}
