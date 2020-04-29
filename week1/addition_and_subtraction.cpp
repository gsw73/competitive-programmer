//
// Created by Gregory Walter on 4/25/20.
//
// Questions:
// 1.  How do you know you're past the point in the sequence where z could no longer be found?
// 2.  What is the longest sequence possible given constraints (0 <= x, y, z <= 1000)?
// 3.  Searching for z... should ultimately happen as sequence is built.

// Observations:
// 1.  x = y:  sequence alternates between 0 and x
// 2.  x > y:  sequence increases
// 3.  x < y:  sequence decreases
// 4.  for max z = 1000, longest sequence from x = 2, y = 1 i.e., incrementing by 1 and starting from smallest values
// 5.  for min z = 1, longest sequence from x = 999, y = 1000
// 6.  stop checking for z when both odd and even sequences are either > z (case 2) or < z (case 3)

// two alternating sequences:
// 1.  even indices: start at 0 and inc by x-y (which may be negative):  [0, odd, a[0]+x-y, odd, a[2]+x-y...]
// 2.  odd indices:  start x and inc by x-y (which may be negative):  [even, x, even, a[1]+x-y, even, a[3]+x-y...]

// Test Cases
// 1.  stdin = "2 1 3", stdout = "3"
// 2.  stdin = "2 0 3", stdout = "-1"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// #define MYDEBUG

static const unsigned int NUM = 2500;

#ifdef MYDEBUG
void track_values( int index, int val2im1, int val2i );
static int seqA[NUM] = {0};
#endif

int main( int argc, char *argv[] ) {
    int x, y, z;
    unsigned int ind2im1, ind2i;
    int answer = 0;
    int val2im2 = 0; // val[2*i-2]
    int val2im1 = 0; // val[2*i-1]
    int val2i = 0; // val[2*i]

    cin >> x >> y >> z;

    if ( z == 0 ) {
        answer = 0;
    } else if ( x == y ) {
        answer = z == x ? 1 : -1;
    } else {
        for (int i = 1; i < NUM / 2; i++) {
            ind2im1 = 2 * i - 1;
            ind2i = 2 * i;

            val2im1 = val2im2 + x;
            val2i = val2im1 - y;

#ifdef MYDEBUG
            track_values( i, val2im1, val2i );
#endif

            if (val2im1 == z) {
                answer = (signed int)ind2im1;
                break;
            } else if (val2i == z) {
                answer = (signed int)ind2i;
                break;
            } else if ( ( x > y && val2im1 > z && val2i > z ) ||
                    ( x < y && val2im1 < z && val2i < z ) ) {
                answer = -1;
                break;
            }
            // prepare for next iteration
            val2im2 = val2i;
        }
    }

#ifdef MYDEBUG
    cout << "x = " << x << " y = " << y << " z = " << z << endl;
    cout << "partial" << endl;
    for ( int i = 0; i < 20; i++ ) {
        if ( i != 0 ) cout << " ";
        cout << seqA[i];
    }
//    for (int val : seqA) {
//        cout << val << " ";
//    }
    cout << endl;
#endif
    cout << answer << endl;

    return 0;
}

#ifdef MYDEBUG
void track_values( int index, int val2im1, int val2i ) {
    seqA[2*index-1] = val2im1;
    seqA[2*index] = val2i;
}
#endif

