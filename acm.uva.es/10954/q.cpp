#include <stdio.h>
#include <queue>
using namespace std;

int main()
{
	int n, x, y;
	while (scanf("%d", &n) == 1 && n > 0) {
		priority_queue<int> q;
		while (n-- > 0 && scanf("%d", &x) == 1) q.push(-x);

		for (y = 0; q.size() > 1;) {
			x = q.top(); q.pop();
			x += q.top(); q.pop();
			y += -x;
			q.push(x);
		}

		printf("%d\n", y);
	}
	return 0;
}
