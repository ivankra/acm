#include <cstdio>
#include <algorithm>
using namespace std;

int row[6000], rowIndex[6000];
int col[6000], colIndex[6000];

int main()
{
	for (int i = 1; i < 6000; i++)
		row[i] = col[i] = rowIndex[i] = colIndex[i] = i;

	char c;
	int x, y, z;

	while (scanf(" %c %d", &c, &x) == 2) {
		if (c != 'W')
			scanf("%d", &y);

		if (c == 'R') {
			swap(row[x], row[y]);
			rowIndex[row[x]] = x;
			rowIndex[row[y]] = y;
		} else if (c == 'C') {
			swap(col[x], col[y]);
			colIndex[col[x]] = x;
			colIndex[col[y]] = y;
		} else if (c == 'Q') {
			printf("%d\n", (row[x]-1)*5678+col[y]);
		} else { //W
			z = x;
			x = rowIndex[(z-1)/5678+1];
			y = colIndex[(z-1)%5678+1];
			printf("%d %d\n", x, y);
		}
	}

}
