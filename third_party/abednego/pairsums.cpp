#include <iostream>
#include <set>
#include <math.h>

using namespace std;

/*****************************************
 * Set reconstruction from pairwise sums *
 *****************************************
 * Given a multiset S of integers, reconstructs
 * the multiset V such that S is the multiset of
 * pairwise sums of V. Fills in V in sorted order.
 * Returns true if successful and false if confused.
 * #include <set>
 * TESTING:
 *      - UVa 10202: Paisumonious numbers
 *      - TopCoder SRM 182: 1000
 * ACKNOWLEDGEMENTS: Thanks to Stefan Pochmann for
 *         the idea, David Arthur for the generalized
 *         algorithm and Bartholomew Furrow for a
 *         reference implementation.
 * LAST MODIFIED: September 21, 2005
 **/
bool pairsums( int *ans, multiset< int > &seq )
{
    int N = seq.size();
    if( N < 3 ) return false;
    __typeof( seq.end() ) it = seq.begin();
    int a = *it++, b = *it++, i = 2;

    for( ; i * ( i - 1 ) < 2 * N && it != seq.end(); i++, ++it )
    {
        // assume seq[i] = ans[1] + ans[2]
        ans[0] = a + b - *it;
        if( ans[0] & 1 ) continue;
        ans[0] >>= 1;

        // try ans[0] as a possible least element
        multiset< int > seq2 = seq;
        int j = 1;
        while( seq2.size() )
        {
            ans[j] = *seq2.begin() - ans[0];
            for( int k = 0; k < j; k++ )
            {
                __typeof( seq2.end() ) jt = seq2.find( ans[k] + ans[j] );
                if( jt == seq2.end() ) goto hell;
                seq2.erase( jt );
            }
            j++;
        }
        hell:;
        if( j * ( j - 1 ) < 2 * N ) continue;

        // it worked! [modify this to deal with multiple answers]
        return true;
    }
    return false;
}

// DEBUG
int main()
{
    multiset< int > s;
    s.insert( 1 ); s.insert( 1 ); cout << "2 = " << s.size() << endl;
    s.erase( 1 ); cout << "1 = " << s.size() << endl; s.erase( 1 );
    int n; cin >> n;
    for( int i = 0; i < n; i++ ) { int x; cin >> x; s.insert( x ); }
    int ans[n];
    bool rc = pairsums( ans, s );
    cout << "Returned: " << ( rc ? "true" : "false" ) << endl;
    cout << "V:";
    for( int i = 0; i <= ( int )sqrt( 2.0 * n ); i++ )
        cout << " " << ans[i];
    cout << endl;
}
