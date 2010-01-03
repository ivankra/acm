#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef long long LL;

// infimum = union
// supremum = intersection

int W, H;
struct Fig {
	char a[64][64];
};
Fig A, B, Inf, Sup;

int main()
{
	for (int cs = 1; scanf("%d %d", &W, &H) == 2; cs++) {
		if (W == 0 || H == 0) break;

		memset(&A, 0, sizeof(A));
		memset(&B, 0, sizeof(B));
		for (int i = 0; i <= H; i++) {
			char s[1000];
			int c, j;
			do { c = getchar(); } while (c != '\n');
			for (j = 0; (c = getchar()) != '\n'; j++) s[j] = c;
			ungetc('\n', stdin);
			for (j = 0; j < 2*W+1; j++) A.a[i][j] = s[j];
			for (j = 0; j < 2*W+1; j++) B.a[i][j] = s[2*W+2+j];
		}

		memset(&Sup, 0, sizeof(Sup));
		for (int i = 0; i <= H; i++) {
			for (int j = 0; j < 2*W+1; j++) {
				Inf.a[i][j] = A.a[i][j] != ' ' ? A.a[i][j] : B.a[i][j];
				Sup.a[i][j] = (A.a[i][j] == B.a[i][j] ? A.a[i][j] : ' ');
			}
		}

		while (true) {
			bool flag = false;
#define S(I,J) Sup.a[I][J]
			for (int i = 1; i <= H; i++) {
				for (int j = 1; j <= 2*W-1; j++) {
					if (S(i,j)=='|' && S(i+1,j)==' ' && (S(i,j-1)!='_' || S(i,j+1)!='_')) {
						S(i,j) = ' ';
						flag = true;
					}

					if (S(i,j)=='|' && S(i-1,j)==' ' && (S(i-1,j-1)!='_' || S(i-1,j+1)!='_')) {
						S(i,j) = ' ';
						flag = true;
					}

					if (S(i,j)=='_' && S(i,j+2)==' ' && (S(i,j+1)!='|' || S(i+1,j+1)!='|')) {
						S(i,j) = ' ';
						flag = true;
					}

					if (S(i,j)=='_' && S(i,j-2)==' ' && (S(i,j-1)!='|' || S(i+1,j-1)!='|')) {
						S(i,j) = ' ';
						flag = true;
					}

				}
			}

			if (!flag) break;
		}

		printf("Case %d:\n", cs);
		for (int i = 0; i <= H; i++) {
			for (int j = 0; j < 2*W+1; j++) putchar(Inf.a[i][j]);
			putchar(' ');
			for (int j = 0; j < 2*W+1; j++) putchar(Sup.a[i][j]);
			printf("\n");
		}
		printf("\n");
	}
}
