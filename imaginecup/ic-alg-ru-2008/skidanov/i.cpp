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

const int maxn = 10005;
const int maxm = 200005;

int n, m, v, sx, sy;

int fs[maxn];
int nx[maxm];
int to[maxm];
int cs[maxm];
int al[maxm];
int cnt;

bool pp[maxn];
bool p[maxn];
int dst[maxn];
set< pair< int, int > > st;

int nm[maxn];
int fr[maxn];

void adde( int a, int b, int c, int l )
{
	nx[cnt] = fs[a];
	fs[a] = cnt;
	to[cnt] = b;
	cs[cnt] = c;
	al[cnt] = l;
	++ cnt;
}

int main( )
{
	int i, j, k;

//	freopen( "in.txt", "r", stdin );

	scanf( "%d %d %d %d", &n, &v, &sx, &sy );
	-- sx; -- sy;
	memset( fs, -1, sizeof( fs ) );

	fi( n )
	{
		scanf( "%d", &k );
		fj( k )
		{
			int a, b, c;
			scanf( "%d %d %d", &a, &b, &c );
			-- a;
			adde( i, a, b, c * v );
		}
	}

	pp[sx] = 1;
	dst[sx] = 0;
	st.insert( mp( 0, sx ) );

	while( !st.empty( ) )
	{
		pair< int, int > cur = * st.begin( );
		st.erase( st.begin( ) );
		int id = cur.second;
		int l = cur.first;
		p[id] = true;

		for( i = fs[id]; i != -1; i = nx[i] ) if( !p[to[i]] )
		{
			int nd = l + cs[i];
			if( nd > al[i] ) continue;
			if( !pp[to[i]] || dst[to[i]] > nd )
			{
				st.erase( mp( dst[to[i]], to[i] ) );
				pp[to[i]] = 1;
				dst[to[i]] = nd;
				fr[to[i]] = id;
				nm[to[i]] = nm[id] + 1;
				st.insert( mp( dst[to[i]], to[i] ) );
			}
		}
	}

	if( !p[sy] ) printf( "0\n" );
	else
	{
		vector< int > ans;
		printf( "%d\n", nm[sy] + 1 );
		int id = sy;
		ans.pb( sy );
		do
		{
			id = fr[id];
			ans.pb( id );
		} while( id != sx );
		reverse( all( ans ) );
		fi( ans.size( ) )
		{
			printf( "%d%c", ans[i] + 1, " \n"[i == ans.size( ) - 1] );
		}
	}

	return 0;
}
