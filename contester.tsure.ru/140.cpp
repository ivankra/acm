#include <cstdio>
#include <cstring>
#include <cstdlib>

char W[100000][10], u[16];
int n, m, k=0;

int cmp(const void *p, const void *q) { return strcmp((char *)p, (char *)q); }

int main()
{
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
                scanf(" %s", W[i]);
        qsort(W, n, sizeof(W[0]), cmp);

        for (scanf("%d", &m); m-- > 0 && scanf(" %s", u) == 1;) {
                while (k < n && strcmp(W[k], u) < 0) printf("%s\n", W[k++]);
                if (k < n && strcmp(W[k], u) == 0)
                        printf("%s - two times\n", W[k++]);
                else
                        printf("%s\n", u);
        }

        while (k < n) printf("%s\n", W[k++]);
        return 0;
}
