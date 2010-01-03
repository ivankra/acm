#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

const int MOD = 123456789;

typedef vector<int> TInput;
typedef int TOutput;

istream &operator >>(istream &stream, TInput &arg)
{
    int N;
    stream >> N;
    arg.resize(N);
    for (int i = 0; i < N; i++)
        stream >> arg[i];
    return stream;
}

TOutput solve(TInput keys)
{
    int N = keys.size();
    sort(keys.begin(), keys.end());

    // f[a][b] is number of trees with keys {keys[a], ..., keys[b-1]}
    // 0 <= a <= b <= N
    int f[401][401];

    // base case: 0-element (empty) trees
    for (int a = 0; a <= N; a++)
        f[a][a] = 1;

    for (int size = 1; size <= N; size++) {
        for (int a = 0; a + size <= N; a++) {
            int b = a + size;
            f[a][b] = 0;
            for (int c = a; c < b; c++) {
                if (c == a || keys[c-1] < keys[c])
                    f[a][b] = (f[a][b] + f[a][c] * (long long)f[c+1][b]) % MOD;
            }
        }
    }
    
    return f[0][N];
}

int main()
{
    TInput in;
    cin >> in;
    cout << solve(in) << endl;
    return 0;
}
