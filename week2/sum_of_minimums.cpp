//
// Created by Gregory Walter on 5/3/20.
//
// A[1..n] is an array of integers.  For 1 ≤ l ≤ r ≤ n, let
// m(l,r) = min{A[l], A[l+1],..., A[r]} is the minimum value of A on interval [l,r].
// Given an array A, find the sum of minimums for all intervals i.e., ∑m(l,r).
//
// INPUT:
// line 1:  integer n (1 ≤ n ≤ 2000), the length of the array
// line 2:  integers A[1], A[2], ..., A[n] (1 ≤ A[i] ≤ 1,000,000)
// OUTPUT:
// sum of minimums

#include <cinttypes>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// #define MYDEBUG

void get_input( uint32_t *, vector<uint32_t>& );
void show_vector( uint32_t, vector<uint32_t>& );
inline uint32_t min(uint32_t a, uint32_t b ) { if ( a < b ) return a; else return b; }

int main( int argc, char *argv[] ) {
    uint32_t n;
    vector<uint32_t>vector_A;
    uint64_t sum_of_mins = 0;
    uint32_t current_min = 0;

    get_input( &n, vector_A );

#ifdef MYDEBUG
    show_vector( n, vector_A );
    uint32_t intervals = 0;
#endif

    for ( auto left = 1; left < n + 1; left++ ) {
        for ( auto right = left; right < n + 1; right++ ) {
            if ( left == right )
                current_min = vector_A[left];
            else
                current_min = min(current_min, vector_A[right]);
            sum_of_mins += current_min;
#ifdef MYDEBUG
            intervals++;
            if ( right != left ) cout << " ";
            cout << "(" << left << ", " << right << "):  " << current_min;
#endif
        }
#ifdef MYDEBUG
        cout << endl;
#endif
    }
#ifdef MYDEBUG
    cout << "Total intervals:  " << intervals << endl;
#endif
    cout << sum_of_mins << endl;

    return 0;
}

void get_input( uint32_t *n, vector<uint32_t> &v ) {
    uint32_t val;

    // n, length of array
    cin >> *n;

    // A, array values -- don't use location [0] to match problem statement
    v.push_back(0);
    for ( auto i = 1; i < *n + 1; i++ ) {
        cin >> val;
        v.push_back( val );
    }
}

void show_vector( uint32_t n, vector<uint32_t> &v ) {
    cout << "Value of n = " << n << endl;
    for ( auto i = 1; i < n + 1; i++ ) {
        if ( i != 1 ) cout << " ";
        cout << v[i];
    }
    cout << endl;
}
