/**
 *  //////////////////////////////
 *  // Stoer-Wagner Minimum Cut //
 *  //////////////////////////////
 *
 * MAIN FUNCTION: minCut( n )
 *      Takes an undirected, weighted graph and returns the weight
 *      of the minimum cut in it. A cut is a set of edges that,
 *      when removed, disconnects the graph. A minimum cut is a
 *      cut of minimum total weight.
 * ALGORITHM:
 *      This is a O(n^3) implementation of the Stoer-Wagner
 *      deterministic algorithm (no randomization is required).
 **/
// Maximum number of vertices in the graph
#define NN 256

// Maximum edge weight (MAXW * NN * NN must fit into an int)
#define MAXW 1000

// Adjacency matrix and some internal arrays
int g[NN][NN], v[NN], w[NN], na[NN];
bool a[NN];

int minCut( int n ){
    // init the remaining vertex set
    for( int i = 0; i < n; i++ ) v[i] = i;

    // run Stoer-Wagner
    int best = MAXW * n * n;
    while( n > 1 ){
        // initialize the set A and vertex weights
        a[v[0]] = true;
        for( int i = 1; i < n; i++ ){
            a[v[i]] = false;
            na[i - 1] = i;
            w[i] = g[v[0]][v[i]];
        }

        // add the other vertices
        int prev = v[0];
        for( int i = 1; i < n; i++ ){
            // find the most tightly connected non-A vertex
            int zj = -1;
            for( int j = 1; j < n; j++ )
                if( !a[v[j]] && ( zj < 0 || w[j] > w[zj] ) )
                    zj = j;

            // add it to A
            a[v[zj]] = true;

            // last vertex?
            if( i == n - 1 ){
                // remember the cut weight
                best <?= w[zj];

                // merge prev and v[zj]
                for( int i = 0; i < n; i++ )
                    g[v[i]][prev] = g[prev][v[i]] += g[v[zj]][v[i]];
                v[zj] = v[--n];
                break;
            }
            prev = v[zj];

            // update the weights of its neighbours
            for( int j = 1; j < n; j++ ) if( !a[v[j]] )
                w[j] += g[v[zj]][v[j]];
        }
    }
    return best;
}

int main()
{
    // read the graph's adjacency matrix into g[][]
    // and set n to equal the number of vertices
    int n, answer = minCut( n );
    return 0;
}
