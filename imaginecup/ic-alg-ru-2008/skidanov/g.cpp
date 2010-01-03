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

const int maxc = 12;
const int maxn = 60005;
const int maxm = 1000005;

const int WIN = 1;
const int LOSE = 2;

int n, m, la;
int a[maxc];
char sm[maxc][maxc];
char bsm[maxc][maxc];
int sx, sy;

int pr[maxc];

int pwr[maxn];
int fs[maxn];
int to[maxm];
int nx[maxm];
int cnt;
int vn;

bool p[maxc];
int b[maxc]; 

int ours[maxc];
int bn, bm;

int ans[maxn];
int q[maxn];
int qn;

bool p2[maxn];
int q2[maxn];
int q2n;

int num;

bool inc( int id )
{
	if( id == -1 ) return false;
	++ pr[id];
	if( pr[id] > n - num + id )
	{
		if( !inc( id - 1 ) ) return false;
		pr[id] = pr[id - 1] + 1;
	}
	return true;
} 

bool rec( int id )
{
	if( p[id] ) return false;
	p[id] = true;

	int i;
	fi( bn ) if( bsm[i][id] && ( b[i] == -1 || rec( b[i] ) ) )
	{
		b[i] = id;
		return true;
	}

	return false;
}

bool bipartite( )
{
	int i, ret = 0;
	memset( b, -1, sizeof( b ) );
	fi( bm )
	{
		memset( p, 0, sizeof( p ) );
		if( !rec( i ) ) return false;
	}
	return true;
}

int encode( )
{
	int i;
	int ret = 0;

	for( i = n - 1; i >= 0; -- i )
		ret = ret * 3 + a[i];

	return ret;
}

void decode( int v )
{
	int i;
	fi( n )
	{
		a[i] = v % 3;
		v /= 3;
	}
}

void adde( int a, int b )
{
	if( a == b ) return;
	nx[cnt] = fs[a];
	fs[a] = cnt;
	to[cnt] = b;
	++ cnt;
}

int main( )
{
	int i, j, k;

//	freopen( "in.txt", "r", stdin );

	scanf( "%d %d %d %d", &n, &m, &sx, &sy );
	memset( fs, -1, sizeof( fs ) );
	fi( m )
	{
		int a, b;
		scanf( "%d %d", &a, &b );
		-- a; -- b;
		sm[a][b] = sm[b][a] = 1;
	}
	a[sx - 1] = 1;
	a[sy - 1] = 2;

	sx = encode( );

	vn = 1;
	fi( n ) vn *= 3;

	q2[q2n ++] = sx;
	for( int ii = 0; ii < q2n; ++ ii )
	{
		i = q2[ii];
		decode( i );

		int moo[3];
		memset( moo, 0, sizeof( moo ) );
		fj( n ) ++ moo[a[j]];
		if( moo[1] && !moo[2] )
		{
			ans[i] = WIN;
			q[qn ++] = i;
		}
		else if( moo[2] && !moo[1] )
		{
			ans[i] = LOSE;
			q[qn ++] = i;
		}

		bn = 0;
		fj( n ) if( a[j] == 1 )
		{
			ours[bn ++] = j;
		}

		fr( num, n / 2 + 1 )
		{
			if( num > bn ) break;
			fj( num )  pr[j] = j;

			do
			{
				bool ok = true;
				fj( num ) if( a[pr[j]] == 1 ) { ok = false; break; }
				if( !ok ) continue;

				memset( bsm, 0, sizeof( bsm ) );

				bm = 0;
				fj( num )
				{
					if( a[pr[j]] == 0 )
					{
						bool ok = false;
						fk( bn ) if( sm[pr[j]][ours[k]] ) { bsm[k][bm] = 1; ok = true; }
						if( !ok ) goto e;
						++ bm;
					}
					else
					{
						bool ok = false;
						fk( bn ) if( sm[pr[j]][ours[k]] ) { bsm[k][bm] = 1; ok = true; }
						if( !ok ) goto e;
						++ bm;
						fk( bn ) if( sm[pr[j]][ours[k]] ) bsm[k][bm] = 1;
						++ bm;
					}
				}
				if( !bipartite( ) ) continue;

				fj( num ) a[pr[j]] = 1;
//				printf( "%d %d\n", i, encode( ) );
				fj( n ) if( a[j] ) a[j] = 3 - a[j];
				la = encode( );
				adde( la, i );
				++ pwr[i];

				if( !p2[la] )
				{
					p2[la] = 1;
					q2[q2n ++] = la;
				}
				
				decode( i );
e:;
			} while( inc( num - 1 ) );
		}
	}

	fi( qn )
	{
		for( j = fs[q[i]]; j != -1; j = nx[j] ) if( !ans[to[j]] )
		{
			if( ans[q[i]] == LOSE )
			{
				ans[to[j]] = WIN;
				q[qn ++] = to[j];
			}
			else
			{
				-- pwr[to[j]];
				if( pwr[to[j]] == 0 )
				{
					ans[to[j]] = LOSE;
					q[qn ++] = to[j];
				}
			}
		}
	}

	if( ans[sx] == WIN ) printf( "FIRST\n" );
	else if( ans[sx] == LOSE ) printf( "SECOND\n" );
	else printf( "DRAW\n" );

	return 0;
}
