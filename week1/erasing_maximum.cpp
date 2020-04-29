//
// Created by Gregory Walter on 4/26/20.
//

// A[1..n] array of integers
// Output array without max el; if multiple, remove third occurrence
// A has unique max or at least three max elements
//
// Input
// Line 1:  n (2 <= n <= 100), length of array
// Line 2:  A[1], A[2], ..., A[n] (1 <= A[i] <= 100)
// Output:  n - 1 integers separated by spaces

// Test Cases
// 1.
// Input line 1: 3
// Input line 2: 1 3 2
// Output:  1 2
// 2.
// Input line 1: 7
// Input line 2: 4 1 4 2 4 3 4
// Output:  4 1 4 2 3 4

#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

// #define MYDEBUG

static const unsigned int LEN = 100;

#ifdef MYDEBUG
void showArray( unsigned int n, unsigned int *myA );
#endif

int main( int argc, char *argv[] ) {
    using namespace std;

    unsigned int num;
    unsigned int seqA[LEN] = {0};
    unsigned int max = 0;
    unsigned int max_occurences = 0;
    unsigned int location_to_remove = 0;
    ostringstream seqB_str;

    cin >> num;
    for ( int i = 0; i < num; i++ ) {
        cin >> seqA[i];
    }

#ifdef MYDEBUG
    showArray( num, seqA );
#endif

    for ( int i = 0; i < num; i++ ) {
        if ( seqA[i] > max ) {
            max = seqA[i];
            max_occurences = 1;
            location_to_remove = i;
        } else if ( seqA[i] == max ) {
            max_occurences++;
            if ( max_occurences == 3 ) {
                location_to_remove = i;
            }
        }
    }

    for ( auto i = 0; i < num; i++ ) {
        if ( i != 0 && i != location_to_remove) seqB_str << ' ';
        if ( i != location_to_remove ) {
            seqB_str << seqA[i];
        }
    }

    cout << seqB_str.str() << endl;
    return 0;
}

void showArray( unsigned int n, unsigned int *myA ) {
    unsigned int *tmp_p = myA;

    printf( "array = " );
    for ( int i = 0; i < n; i++ ) {
        printf( "%d ", *tmp_p++ );
    }
    printf("\n");
}


