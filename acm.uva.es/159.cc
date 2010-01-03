#include <cstdio>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

char buffer[64][64];

bool output(int y, int x, string h, string v) {
	for (int i = 0; i < (int)h.size(); i++)
		buffer[y][x+i] = h[i];

	int a = -1, b = -1;
	for (int i = 0; i < (int)h.size(); i++) {
		for (int j = 0; j < (int)v.size(); j++) {
			if (h[i] == v[j]) { a = i; b = j; goto done; }
		}
	}
done:
	if (a < 0) return false;

	for (int j = 0; j < (int)v.size(); j++)
		buffer[y+j-b][x+a] = v[j];

	return true;
}

int main()
{
	string h1, v1, h2, v2;
	for (int cs = 1; cin >> h1 >> v1 >> h2 >> v2; cs++) {
		if (h1[0] == '#') break;

		if (cs > 1) printf("\n");

		memset(buffer, ' ', sizeof(buffer));
		if (!output(32, 0, h1, v1) ||
		    !output(32, h1.size()+3, h2, v2)) {
			printf("Unable to make two crosses\n");
		} else {
			for (int i = 0; i < 64; i++) {
				for (int j = 63; j >= 0 && buffer[i][j] == ' '; j--) buffer[i][j] = 0;
				if (buffer[i][0] == 0) continue;
				printf("%s\n", buffer[i]);
			}
		}
	}
}
