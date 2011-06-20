#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string s;
int n;
int a[2][101000], b[2][101000], c[2][101000];
int cnt[128], cur[128];

void init_steps(int *a, int *b, int *c)
{
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; i++) cnt[s[i]]++;
	cur[0] = 0;
	for (int i = 1; i < 128; i++) cur[i] = cur[i - 1] + cnt[i - 1];
	for (int i = 0; i < n; i++) a[cur[s[i]]++] = i;
	for (int i = 0; i < n; i++)
	{
		b[a[i]] = i;
		if (!i || s[a[i]] != s[a[i - 1]]) c[i] = i;
		else c[i] = c[i - 1];
	}
}

void make_step(int h, int *a1, int *b1, int *c1, int *a2, int *b2, int *c2)
{
	for (int i = 0; i < n; i++) c2[i] = i;
	for (int i = 0; i < n; i++)
	{
		a1[i] = (a1[i] - h + 2 * n) % n;
		a2[c2[c1[b1[a1[i]]]]++] = a1[i];
	}
	for (int i = 0; i < n; i++)
	{
		b2[a2[i]] = i;
		if (!i || c1[b1[a2[i]]] != c1[b1[a2[i - 1]]] || c1[b1[(a2[i] + h) % n]] != c1[b1[(a2[i - 1] + h) % n]]) c2[i] = i;
		else c2[i] = c2[i - 1];
	}
}

int main()
{
	cin >> s;
	s += '$';
	n = int(s.size());
	init_steps(a[0], b[0], c[0]);
	int u = 0, v = 1, h = 1;
	while (h < n)
	{
		make_step(h, a[u], b[u], c[u], a[v], b[v], c[v]);
		swap(u, v);
		h *= 2;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = a[u][i]; j < n; j++)
			printf("%c", s[j]);
		printf("\n");
	}
	return 0;
}
