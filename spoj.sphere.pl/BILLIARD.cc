#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

int main() {
	double PI = 2 * acos(0.0);
	int a,b,s,m,n;
	while (cin >> a >> b >> s >> m >> n) {
		if ((a|b|s|m|n) == 0) break;
		double dx = m*a;
		double dy = n*b;
		double ang = atan2(dy, dx) * 180 / PI;
		double v = sqrt(dx*dx + dy*dy) / s;
		printf("%.2f %.2f\n", ang, v);
	}
}
