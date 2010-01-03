#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

// Returns a longest strictly-increasing subsequence.
template<typename T> vector<T> lis(const vector<T> &a) {
    vector<T> b;
    vector<size_t> len(a.size());

    size_t i, k = 0;
    for (i = 0; i < a.size(); i++) {
        // invariant: b[j] is the smallest number that ends
        // a strictly-increasing subsequence of length j+1 of a[0..i-1];
        // len[j] = length of LIS ending at a[j] for all j=0..i-1
        if (k == 0 || b.back() < a[i]) {
            b.push_back(a[i]);
            len[i] = ++k;
        } else {
            size_t j = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
            b[j] = a[i];
            len[i] = j+1;
        }
    }

    // Reconstruct some LIS
    const T *last = 0;
    for (i = a.size(); i-- != 0;)
        if (len[i] == k && (last == 0 || a[i] < *last)) { b[--k] = a[i]; last = &a[i]; }
    return b;
}

int main()
{
    int a[] = { 1, 2, 2, 6, 4, 4, 5, 5, 0 };
    vector<int> v(a, a+sizeof(a)/sizeof(a[0]));
    v = lis(v);
    for (int i = 0; i < v.size(); i++) printf("%d ", v[i]); printf("\n");
}
