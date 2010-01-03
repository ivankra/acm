#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> read() {
	vector<int> res;
	int x;
	while (scanf("%d", &x) == 1 && x != -1)
		res.push_back(x);
	sort(res.begin(), res.end());
	return res;
}

int main()
{
	vector<int> a = read(), b = read(), c;

	for (int i = 0, j = 0; i < (int)a.size() && j < (int)b.size();) {
		if (a[i] == b[j]) {
			c.push_back(a[i]); i++; j++;
		} else if (a[i] < b[j]) {
			i++;
		} else {
			j++;
		}
	}

	if (c.size() == 0)
		printf("empty\n");
	else
		for (int i = 0; i < (int)c.size(); i++)
			printf(i+1 < (int)c.size() ? "%d " : "%d\n", c[i]);
}
