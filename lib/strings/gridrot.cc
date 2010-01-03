#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

vector<string> transpose(const vector<string> &a) {
	int n = a.size(), m = (n > 0 ? a[0].size() : 0);
	vector<string> b(m, string(n, ' '));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			b[j][i] = a[i][j];
	return b;
}

// Rotates a 2D grid clockwise
vector<string> rot_cw(const vector<string> &a) {
	int n = a.size(), m = (n > 0 ? a[0].size() : 0);
	vector<string> b(m, string(n, ' '));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			b[j][n-1-i] = a[i][j];
	return b;
}

// Rotates a 2D grid counter-clockwise
vector<string> rot_ccw(const vector<string> &a) {
	int n = a.size(), m = (n > 0 ? a[0].size() : 0);
	vector<string> b(m, string(n, ' '));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			b[m-1-j][i] = a[i][j];
	return b;
}


/*
void prn(vector<string> v) {
	for (int i = 0; i < (int)v.size(); i++)
		printf("%s\n", v[i].c_str());
	printf("\n");
}

int main() {
	vector<string> a;
	a.push_back("..x..q;1");
	a.push_back("xxxy..,2");
	a.push_back("..xz.w.3");
	prn(a);
	prn(transpose(a));
	prn(rot_cw(a));
	prn(rot_ccw(a));
}
*/
