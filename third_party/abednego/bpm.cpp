/**
 *   ////////////////////////
 *   // BIPARTITE MATCHING //
 *   ////////////////////////
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2003
 * Contact author:
 *      igor at cs.ubc.ca
 **/

/**********************
 * Bipartite matching * O(m*n^2))
 **********************
 * Given a bipartite graph represented as an m-by-n matrix, where graph[i][j]
 * is true iff there is an edge from pigeon i to hole j, computes the maximum
 * number of pigeons that can find a hole (one per pigeon) and an optimal
 * assignment.
 *      Formally, this is a stripped down version of Ford-Fulkerson with
 * DFS used to find an augmenting path. DFS does the job quickly because
 * capacities can only be 0 or 1.
 *
 * PARAMETERS:
 *      - graph: adjacency matrix as above.
 * RETURNS:
 *      - an integer corresponding to the number of assignments
 *      - matchL[m]: for each pigeon, a hole or -1
 *      - matchR[n]: for each hole, a pigeon or -1
 * DETAILS:
 *      - graph[m][n], matchL[n], matchR[m] and seen[m] are global arrays
 *      - main() initializes matchL[] and matchR[] to all -1.
 *      - main() does a loop over all pigeons i and in each iteration
 *          - clears seen[] to all 0
 *          - calls bpm(i) and increments the maxflow counter
 *      - bpm(i) returns true iff pigeon i can be assigned a hole
 * ACKNOWLEDGEMENTS:
 *      - Thanks to tjq from TopCoder for a reference implementation.
 * FIELD TESTING:
 *      - Valladolid 10080: Gopher (II)
 *      - Valladolid 10092: The Problem with the Problem Setter
 *      - Valladolid 670:   The dog task
 *      - Valladolid 259:   Software Allocation
 * #include <string.h>
 **/

#include <string.h>

#define M 128
#define N 128

bool graph[M][N];
bool seen[N];
int matchL[M], matchR[N];
int n, m;

bool bpm( int u )
{
    for( int v = 0; v < n; v++ ) if( graph[u][v] )
    {
        if( seen[v] ) continue;
        seen[v] = true;

        if( matchR[v] < 0 || bpm( matchR[v] ) )
        {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

int main()
{
    // Read input and populate graph[][]
    // Set m, n

    memset( matchL, -1, sizeof( matchL ) );
    memset( matchR, -1, sizeof( matchR ) );
    int cnt = 0;
    for( int i = 0; i < m; i++ )
    {
        memset( seen, 0, sizeof( seen ) );
        if( bpm( i ) ) cnt++;
    }

    // cnt contains the number of happy pigeons
    // matchL[i] contains the hole of pigeon i or -1 if pigeon i is unhappy
    // matchR[j] contains the pigeon in hole j or -1 if hole j is empty

    return 0;
}
