#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

void rot(char s[], int a, int b, int c) {
	int t = s[a];
	s[a] = s[b];
	s[b] = s[c];
	s[c] = t;
}

int main()
{
	char s[10], t[10];
	scanf(" %s %s", s, t);

	for (int i = 0; i < 3; i++, rot(s,0,1,2)) {
		for (int j = 0; j < 3; j++, rot(s,0,1,3)) {
			for (int k = 0; k < 3; k++, rot(s,1,2,3)) {
				if (strcmp(s, t) == 0) {
					printf("equal\n");
					return 0;
				}
			}
		}
	}

	printf("different\n");
}
