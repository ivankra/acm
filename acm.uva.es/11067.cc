#include <cstdio>
#include <cstring>
#include <cctype>
#define MAX 128

char block[MAX][MAX];
long long ways[MAX];

int main() {
	int width, height;

	while (scanf("%d %d", &width, &height)==2 && width>0 && height>0) {
		int bn, br, bc;
		scanf("%d", &bn);
		memset(block, 0, sizeof(block));
		while (bn-- > 0 && scanf("%d %d", &bc, &br)==2)
			block[br][bc] = 1;

		memset(ways, 0, sizeof(ways));
		ways[0] = 1;

		for (int r = 0; r <= height; r++)
			for (int c = 0; c <= width; c++)
				if (block[r][c])
					ways[c] = 0;
				else
					ways[c] += (c>0 ? ways[c-1] : 0);

		long long res = ways[width];
		if (res > 1)
			printf("There are %lld paths from Little Red Riding Hood's house to her grandmother's house.\n",res);
		else if (res == 1)
			printf("There is one path from Little Red Riding Hood's house to her grandmother's house.\n");
		else
			printf("There is no path.\n");
	}

}
