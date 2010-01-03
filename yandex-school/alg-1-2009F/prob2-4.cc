#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> VI;

void always_assert(bool foo)
{
    assert(foo);
}

vector<VI> read_input()
{
    int number, blockSize;
    always_assert(2 == scanf("%d %d", &number, &blockSize));

    vector<VI> res(number, VI(blockSize));
    for (int i = 0; i < number; i++) {
        for (int j = 0; j < blockSize; j++) {
            always_assert(1 == scanf("%d", &res[i][j]));
            always_assert(j == 0 || res[i][j-1] <= res[i][j]);
        }
    }
    return res;
}

VI join(const vector<VI> &input)
{
    VI output;
    for (size_t i = 0; i < input.size(); i++)
        output.insert(output.end(), input[i].begin(), input[i].end());
    return output;
}

VI solve(const vector<VI> &input)
{
    size_t blockSize = input[0].size();       // initial size of sorted blocks
    size_t number = input.size() * blockSize; // total number of elements to sort

    VI buffers[2] = { join(input), VI(number) };
    int currentBuffer = 0;

    // here we just do bottom-up merge sort, starting with block size m.
    for (; blockSize < number; blockSize *= 2, currentBuffer ^= 1) {
        VI &cur = buffers[currentBuffer];
        VI &next = buffers[currentBuffer ^ 1];

        size_t i;
        for (i = 0; i + blockSize < number; i += 2 * blockSize) {
            size_t m = blockSize;
            merge(
                &cur[i], &cur[i+m],                   // input 1
                &cur[i+m], &cur[min(number, i+2*m)],  // input 2
                &next[i]                              // output
            );
        }

        if (i < number)
            copy(&cur[i], &cur[number], &next[i]);
    }

    return buffers[currentBuffer];
}

void write_output(const VI &output)
{
    for (size_t i = 0; i < output.size(); i++)
        printf(i == 0 ? "%d" : " %d", output[i]);
    printf("\n");
}

int main()
{
    write_output(solve(read_input()));
    return 0;
}
