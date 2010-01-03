#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int main()
{
	int F[100], R[100], NF, NR;
	while (scanf("%d %d", &NF, &NR) == 2 && NF>0) {
		for (int i = 0; i < NF; i++) scanf("%d", &F[i]);
		for (int i = 0; i < NR; i++) scanf("%d", &R[i]);

		vector<double> v;
		for (int i = 0; i < NF; i++)
			for (int j = 0; j < NR; j++)
				v.push_back(R[j] / (double)F[i]);

		sort(v.begin(), v.end());

		double res = 0;
		for (int i = 1; i < (int)v.size(); i++)
			res >?= v[i] / v[i-1];
		printf("%.2f\n", res);
	}
}
