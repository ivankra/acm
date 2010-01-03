#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;
typedef unsigned char byte;

class BitStream {
	byte *data;
	int size, head;

public:
	BitStream(byte *begin, byte *end) {
		data = begin;
		size = end - begin;
		head = 0;
	}

	bool eof() const {
		return head >= 8 * size;
	}

	int read() {
		int t = (data[head >> 3] >> (7 - (head & 7))) & 1;
		head++;
		return t;
	}

	int readInt(int bitlen) {	// big-endian
		int res = 0;
		for (int i = bitlen-1; i >= 0; --i)
			res |= read() << i;
		return res;
	}
};

class Huffman {
	int N, L[400], code[400];
	int treeSym[1024], treeNext[1024][2], treeN;

public:
	Huffman(int N) : N(N) { }

	void setLength(int symbol, int length) {
		L[symbol] = length;
		assert(length <= 23);
	}

	void generate() {
		memset(code, 0, sizeof(code));
		for (int len = 23, m = 0, first = 1; len >= 1; len--, m >>= 1) {
			for (int i = 0; i < N; i++) {
				if (L[i] != len) continue;

				if (first) {
					first = 0;
				} else {
					m++;
					assert(0 <= m && m < (1 << len));
				}

				code[i] = m;
			}
		}

#if 0
		printf("huffman codes:\n");
		for (int i = 0; i < N; i++) {
			if (L[i] == 0) continue;
			printf("%5d %c len=%-3d code=", i, (i >= 32 ? i : ' '), L[i]);
			for (int j = L[i]-1; j >= 0; j--)
				printf("%d", (code[i] >> j) & 1);
			printf("\n");
		}
#endif

		memset(treeSym, 0xff, sizeof(treeSym));
		memset(treeNext, 0, sizeof(treeNext));
		treeN = 1;

		for (int symbol = 0; symbol < N; symbol++) {
			if (L[symbol] == 0) continue;

			int p = 0;
			for (int j = L[symbol]-1; j >= 0; j--) {
				assert(treeSym[p] < 0);
				int bit = (code[symbol] >> j) & 1;
				if (treeNext[p][bit] == 0)
					treeNext[p][bit] = treeN++;
				p = treeNext[p][bit];
			}

			treeSym[p] = symbol;
		}
	}

	int read(BitStream &bits) {
		int p = 0;
		while (true) {
			if (treeSym[p] >= 0) return treeSym[p];
			if (bits.eof()) return -1;
			p = treeNext[p][bits.read()];
			assert(p != 0);
		}
	}
};

bool readHexByte(byte &res) {
	res = 0;
	for (int i = 0; i < 2; i++) {
		while (true) {
			int c = getchar();
			if (c == EOF) return false;
			if ('0' <= c && c <= '9') { res = res * 16 + c - '0'; break; }
			if ('A' <= c && c <= 'F') { res = res * 16 + c - 'A' + 10; break; }
			if ('a' <= c && c <= 'f') { res = res * 16 + c - 'a' + 10; break; }
		}
	}
	return true;
}

int exactLog2(int n) {
	assert(n > 0);
	for (int i = 0; i < 30; i++)
		if (n == (1 << i)) return i;
	assert(0 == 1);
	return 0;
}

void decompress(byte *input, int size)
{
	assert(*(unsigned *)input == 0x0472414B);

	BitStream bits(input+8, input+size);

	Huffman huffAux(24);
	for (int i = 0; i < 24; i++)
		huffAux.setLength(i, bits.readInt(4));
	huffAux.generate();

	Huffman huffMain(256+32);
	for (int i = 0; i < 256+32; i++) {
		int s = huffAux.read(bits);
		assert(0 <= s && s < 24);
		huffMain.setLength(i, s);
	}
	huffMain.generate();

	Huffman huffL(32);
	for (int i = 0; i < 32; i++) {
		int s = huffAux.read(bits);
		assert(0 <= s && s < 24);
		huffL.setLength(i, s);
	}
	huffL.generate();

	int outputSize = *(unsigned *)(input + 4);
	byte *output = (byte *)malloc(outputSize + 100);

	int seq[50] = { 1, 2 };
	for (int n = 2; n < 50; n++) {
		int k = n/2;
		if (n % 2 == 0)
			seq[n] = (1<<k) + (1<<(k-1));
		else
			seq[n] = 1<<(k+1);
	}

	for (int pos = 0; pos < outputSize;) {
		assert(!bits.eof());

		int i = huffMain.read(bits);
		if (0 <= i && i < 256) {
			output[pos++] = i;
		} else {
			i -= 256;
			int x = seq[i] + bits.readInt(exactLog2(seq[i+1] - seq[i]));

			int j = huffL.read(bits);
			int l = seq[j] + bits.readInt(exactLog2(seq[j+1] - seq[j]));

			assert(pos - x >= 0);
			for (int q = pos - x; pos < outputSize && l > 0; l--)
				output[pos++] = output[q++];
		}

	}

	for (int i = 0; i < outputSize; i++)
		printf("%.2X", output[i]);
	printf("\n");

	free(output);
}

int main() {
	int size = 0, allc = 512*1024;
	byte *input = (byte *)malloc(allc);

	while (true) {
		if (size+10 > allc) {
			allc *= 2;
			input = (byte *)realloc(input, allc);
		}
		if (!readHexByte(input[size])) break;
		size++;
	}

	decompress(input, size);
}
