//
// Created by Gregory Walter on 5/2/20.
//

// A is a symmetric matrix of intergers, n x n
// permutation, p, of integers from 1 to n has a cost defined as
// SUM(i = 1 to i = n - 1) A[p(i)][p(i+1)]
//
// INPUT:
// first line:  n, (1 <= n <= 9)
// next n lines:  each contains n integers A[i][j] (0 <= A[i][j] <= 1000),
//                A[i][i] = 0 for all 1 <= i <= n
//
// OUTPUT:
// integers 1 to n in some order separated by spaces representing a
//      permutation of minimum cost; if multiple mins exist, output any of them

#include <cinttypes>
#include <iostream>
#include <vector>
#include <array>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::array;

// #define MYDEBUG

static const uint32_t SQ_MATRIX_MAX = 10;

void get_input( uint32_t *n, vector<vector<uint32_t>> & matrix );
void show_matrix( uint32_t n, vector<vector<uint32_t>> & matrix );

int32_t permutation( uint32_t, uint32_t, array<uint32_t, SQ_MATRIX_MAX> &, vector<vector<uint32_t>> &, array<uint32_t, SQ_MATRIX_MAX> & );
uint32_t get_cost( uint32_t last, array<uint32_t, SQ_MATRIX_MAX> &pi, vector<vector<uint32_t>> &matrix );

int main( int argc, char *argv[] ) {
    uint32_t n;
    vector<vector<uint32_t>> matrix(SQ_MATRIX_MAX, vector<uint32_t>(SQ_MATRIX_MAX, 0));
    array<uint32_t, SQ_MATRIX_MAX> pi{0};
    array<uint32_t, SQ_MATRIX_MAX> min_pi{0};
    int32_t min_cost = 0;

    get_input( &n, matrix );
#ifdef MYDEBUG
    show_matrix( n, matrix );
#endif

    // initialize pi
    for ( auto i = 1; i < n + 1; i ++ ) {
        pi[i] = i;
    }

#ifdef MYDEBUG
    cout << "original pi:  " << endl;
    for ( auto val : pi ) cout << val << " ";
    cout << endl;
    cout << endl;
#endif

    min_cost = permutation( 1, n, pi, matrix, min_pi );
#ifdef MYDEBUG
    cout << "min_cost = " << min_cost << endl;
#endif
    for ( auto i = 1; i < n + 1; i++ ) {
        if ( i != 1 ) cout << " ";
        cout << min_pi[i];
    }
    cout << endl;

    return 0;
}

uint32_t get_cost( uint32_t last, array<uint32_t, SQ_MATRIX_MAX> &pi, vector<vector<uint32_t>> &matrix ) {
    uint32_t cost = 0;

    for ( auto i = 1; i < last; i++ ) {
        cost += matrix[pi[i]][pi[i+1]];
    }
    return cost;
}

int32_t permutation( uint32_t first, uint32_t last, array<uint32_t, SQ_MATRIX_MAX> & pi, vector<vector<uint32_t>> & matrix, array<uint32_t, SQ_MATRIX_MAX> & min_pi ) {
#ifdef MYDEBUG
    static uint32_t calls = 0;
    static uint32_t perm = 0;
    calls++;
#endif
    static int32_t min_cost = -1;
    uint32_t cost;

    if ( first == last ) {
        cost = get_cost( last, pi, matrix );
        if ( cost < min_cost || min_cost == -1 ) {
            min_cost = cost;
            min_pi = pi;
        }
#ifdef MYDEBUG
        perm++;
        cout << "CALL" << calls <<  " first = " << first << " last = " << last << endl;
        cout << "PERM" << perm << "(" << cost << "):  ";
        // print out whole thing because we're done
        for ( auto i = 1; i < last + 1; i++ ) {
            if (i != 1) cout << " ";
            cout << pi[i];
        }
        cout << endl;
#endif
    } else {
        for ( auto j = first; j < last + 1; j++ ) {
#ifdef MYDEBUG
            cout << "CALL" << calls << " iter = " << j << " first = " << first << " last = " << last << endl;
#endif
            std::swap(pi[first], pi[j]);
            permutation( first + 1, last, pi, matrix, min_pi );
            std::swap(pi[first], pi[j]);
        }
    }
    return min_cost;
}

void get_input( uint32_t *n, vector<vector<uint32_t>> & matrix ) {
    // n, permutation length and matrix dimension
    cin >> *n;

    // matrix, row by row
    // skipping element 0, as problem statement describes 1..9 x 1..9 matrix
    for ( auto i = 1; i < (*n + 1); i++ )
        for ( auto j = 1; j < (*n + 1); j++ )
            cin >> matrix[i][j];
}

void show_matrix( uint32_t n, vector<vector<uint32_t>> & matrix ) {
    cout << "Matrix dimensions:  " << n << " x " << n << endl;
    for ( auto i = 1; i < (n+1); i++ ) {
        for (auto j = 1; j < (n + 1); j++) {
            if (j != 1) cout << " ";
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

