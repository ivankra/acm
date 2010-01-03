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

const int maxn = 505;
const int maxp = 6;

long long n;
vector< int > divs;
long long d[maxn][maxp][maxp];

int p2[3] = { 1, 2, 4 };
int p5[3] = { 1, 5, 25 };

int main( )
{
	int i, j, k;

//	freopen( "in.txt", "r", stdin );

	scanf( "%lld", &n );

	fi( 101 ) if( i ) if( 100 % i == 0 ) divs.pb( i );

	d[1][0][0] = 1;

	int ii, jj;
	fi( maxn ) if( i )
	{
		bool ok = false;
		fj( maxp ) fk( maxp ) if( d[i][j][k] )
		{
			ok = true;
			long long oval = d[i][j][k];
			fr( ii, 3 ) if( ii <= j ) fr( jj, 3 ) if( jj <= k )
			{
				long long add = d[i][j][k] / p2[ii] / p5[jj];
				long long val = oval;

				while( 1 )
				{
					if( n - add < val ) break;
					val += add;
					if( val - oval > oval ) break;
					int nj = 0;
					int nk = 0;
					long long moo = val;
					while( moo % 2 == 0 )
					{
						++ nj;
						moo /= 2;
					}
					while( moo % 5 == 0 )
					{
						++ nk;
						moo /= 5;
					}
					if( nj >= maxp ) nj = maxp - 1;
					if( nk >= maxp ) nk = maxp - 1;
					if( d[i + 1][nj][nk] == 0 || d[i + 1][nj][nk] > val )
						d[i + 1][nj][nk] = val;
				}
			}
		}
		if( !ok )
		{
			-- i;
			printf( "%d\n", i - 1 );
			return 0;
		}
	}

	return 0;
}
