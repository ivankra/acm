/*
ID: infnty1
PROB: preface
LANG: C
*/
#include <stdio.h>
#include <string.h>

int c[256];

struct { int x; char *s; } tab[] = {
	{1000,"M"}, {900,"CM"}, {500,"D"}, {400,"CD"}, {100,"C"},
	{90,"XC"}, {50,"L"}, {40,"XL"}, {10,"X"},
	{9,"IX"}, {5,"V"}, {4,"IV"}, {1,"I"}, {0,""}
};

void add(char *s) {for(;*s;s++)c[*s]++;}

void go(int n)
{
	int i;
	for (i = 0; tab[i].x; i++)
		for (; n >= tab[i].x; n -= tab[i].x) add(tab[i].s);
}

int main()
{
	int i, j, N;
	freopen("preface.in", "r", stdin);
	freopen("preface.out", "w", stdout);

	scanf("%d", &N);

	memset(c, 0, sizeof(c));
	for (i = 1; i <= N; i++) go(i);
	for (i = 0; i < 7; i++) {
		j = "IVXLCDM"[i];
		if (c[j]) printf("%c %d\n", j, c[j]);
	}

	return 0;
}
