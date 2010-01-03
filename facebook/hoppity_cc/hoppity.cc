#include <cstdio>

int main(int argc, char *argv[])
{
    int n;
    freopen(argv[1], "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        if (i % 15 == 0)
            printf("Hop\n");
        else if (i % 3 == 0)
            printf("Hoppity\n");
        else if (i % 5 == 0)
            printf("Hophop\n");
    }
}
