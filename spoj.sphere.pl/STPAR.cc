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
	int n;
	while (scanf("%d", &n) == 1 && n > 0) {
		vector<int> v(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &v[i]);

		vector<int> stack;
		int head = 0, next = 1;

		while (next <= n) {
			if (stack.size() != 0 && stack.back() == next) {
				stack.pop_back();
				next++;
			} else if (head < v.size()) {
				if (v[head] == next) {
					head++;
					next++;
				} else {
					stack.push_back(v[head++]);
				}
			} else {
				break;
			}
		}

		printf(next > n ? "yes\n" : "no\n");
	}
}
