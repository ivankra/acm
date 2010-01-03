#include <iostream>
using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;

	unsigned long long s[51][51];
	for (int y = 0; y <= m; y++)
		s[n][y] = y==m ? 1 : 0;

	for (int x = n-1; x >= 0; x--)
		for (int y = 0; y <= m; y++)
			s[x][y] = s[x+1][y] + (y < m ? s[x+1][y+1] : 0);

	cout << s[0][0] << endl;
}
