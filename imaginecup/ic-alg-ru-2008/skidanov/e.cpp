#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>

#include <math.h>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <map>

#define fo(a,b,c) for( a = ( b ); a < ( c ); ++ a )
#define fr(a,b) fo( a, 0, ( b ) )
#define fi(a) fr( i, ( a ) )
#define fj(a) fr( j, ( a ) )
#define fk(a) fr( k, ( a ) )
#define pb push_back
#define mp make_pair
#define all(v) (v).begin( ), (v).end( )

using namespace std;

const int maxv = 11;
const int maxl = 1500005;

int n, m;
int num[maxv];
char dg[maxl];
char on[maxl];

int main( )
{
	int i, j, k;

//	freopen( "in.txt", "r", stdin );

	scanf( "%d", &n );

	if( n == 1 )
	{
		printf( "%d\n", 9 );
		return 0;
	}

	fi( 10 ) num[i] = 1;
	int ans = 0;
	fi( 10 ) dg[i] = 1;
	on[1] = 1;
	for( i = 10; i < 15000000; ++ i )
	{
		int digs = dg[i / 10] + 1;
		int ones = on[i / 10] + (( i % 10 == 1 )?1:0);
		if( i < maxl )
		{
			dg[i] = digs;
			on[i] = ones;
		}

		num[10] = num[10 - digs] + ones;
		if( num[10] == n ) ++ ans;
		fj( 10 ) num[j] = num[j + 1];
	}

	printf( "%d\n", ans );

	return 0;
}
