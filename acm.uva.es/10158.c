#include <stdio.h>

int p[65536], war[65536], n;

int find(int x)
{
	int y, z;

	if (x < 0)
		return x;

	for (z = x; p[z] != z; z = p[z]);

	for (; x != z; x = y) {
		y = p[x];
		p[x] = z;
	}

	return z;
}

int are_friends(int x, int y)
{
	return (find(x) == find(y)) ? 1 : 0;
}

int are_enemies(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x == y) return 0;

	war[x] = find(war[x]);
	if (war[x] == y) return 1;

	return 0;
}

int set_friends(int x, int y)
{
	int u, v;

	x = find(x);
	y = find(y);

	if (are_friends(x, y)) return 0;
	if (are_enemies(x, y)) return 1;
	if (x == y) return 0;

	u = find(war[x]);
	v = find(war[y]);

	p[y] = x;

	if (u < 0 && v < 0)
		war[x] = -1;
	else if (u < 0)
		war[x] = v, war[v] = x;
	else if (v < 0)
		war[x] = u, war[u] = x;
	else
		p[v] = u, war[x] = u, war[u] = x;

	return 0;
}

int set_enemies(int x, int y)
{
	int u, v;

	x = find(x);
	y = find(y);

	if (are_enemies(x, y)) return 0;
	if (are_friends(x, y)) return 1;
	if (x == y) return 1;

	u = find(war[x]);
	v = find(war[y]);

	if (u >= 0) p[u] = y;
	if (v >= 0) p[v] = x;

	war[x] = y;
	war[y] = x;

	return 0;
}

int main()
{
	int i, c, x, y;

	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		p[i] = i;
		war[i] = -1;
	}

	while (scanf("%d %d %d", &c, &x, &y) == 3 && c > 0) {
		if (c < 1 || c > 4 || x < 0 || x >= n || y < 0 || y >= n) {
			printf("-1\n");
			continue;

		}

		if (c == 1 && set_friends(x, y)) 
			printf("-1\n");
		else if (c == 2 && set_enemies(x, y))
			printf("-1\n");
		else if (c == 3)
			printf("%d\n", are_friends(x, y));
		else if (c == 4)
			printf("%d\n", are_enemies(x, y));
	}

	return 0;
}
