//
// Created by Gregory Walter on 5/5/20.
//

// The chess king problem:
//
// Place as many kings as possible on a board r x c such that there is at most
// one king in any square and each king has at least on possible move into
// a free cell on the board.
//
// INPUT:
// Two integers, r and c (1 ≤ r, c ≤ 100) separated by spaces
// OUTPUT:
// The maximum number of kings.

#include <cinttypes>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// #define MYDEBUG

uint32_t calculate_kings( uint32_t, uint32_t, uint32_t );

int main( int argc, char *argv[] ) {
    uint32_t row, col;
    uint32_t kings;
    uint32_t rb, cb;

    cin >> row >> col;

#ifdef MYDEBUG
    cout << "read in rows x col:  " << row << " x " << col << endl;
#endif

    // let rb = rows-with-blanks and cb = columns-with-blanks
    rb = row / 3 + ( row % 3 ? 1 : 0 );
    cb = col / 3 + ( col % 3 ? 1 : 0 );

    // kings = full rows * col + rows with blanks * full col
    kings = ( row - rb ) * col + rb * ( col - cb );

    cout << kings << endl;

    return 0;
}

