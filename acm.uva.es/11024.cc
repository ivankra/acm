#include <cstdio>
#include <algorithm>
using namespace std;

int P, S[4][4], A[4][5];

void print() {
        for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 5; j++)
                        printf("%5d", A[i][j]);
                printf("\n");
        }
        printf("\n");
}

int solve() {
//        printf("P=%d   S=%d %d/%d %d\n",P, S[1][1],S[1][2],S[2][1],S[2][2]);

        memset(A, 0, sizeof(A));
        A[0][0]=1; A[0][2]=1; A[0][4]=(P-S[1][1])%P;
        A[1][0]=1; A[1][3]=1; A[1][4]=(P-S[1][2])%P;
        A[2][1]=1; A[2][2]=1; A[2][4]=(P-S[2][1])%P;
        A[3][1]=1; A[3][3]=1; A[3][4]=(P-S[2][2])%P;

        for (int i = 0; i < 4; i++)
        for (int j = 0; j < 5; j++)
                A[i][j] %= P;

//        print();

        int x = A[0][4]-A[1][4]-A[2][4]+A[3][4];
        if (x < 0) x = P - ((-x) % P);
        x %= P;

        return x==0;
}

int main()
{
        int T, p[4][4];
        for (scanf("%d", &T); T-->0;) {
                for (int i = 1; i <= 2; i++)
                        scanf("%d %d %d %d", &S[i][1], &S[i][2], &p[i][1], &p[i][2]);

                P = p[1][1];
                for (int i = 1; i <= 2; i++)
                for (int j = 1; j <= 2; j++)
                        P = __gcd(P, p[i][j]);

                for (int i = 1; i <= 2; i++)
                for (int j = 1; j <= 2; j++)
                        S[i][j] %= P;

                printf(solve() ? "Yes\n" : "No\n");
        }
}
