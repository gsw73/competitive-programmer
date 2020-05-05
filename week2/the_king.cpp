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

#define MYDEBUG

uint32_t calculate_kings( uint32_t, uint32_t, uint32_t );

int main( int argc, char *argv[] ) {
    uint32_t row, col;
    uint32_t sw_row, sw_col;
    uint32_t kings;
    uint32_t rows_with_blanks, rows_filled;

    cin >> row >> col;

    cout << "read in rows x col:  " << row << " x " << col << endl;

    // answer is symmetrical so always deal with something wider than
    // tall so that special cases will always be in the same place
    if ( row > col ) {
        sw_col = row;
        sw_row = col;
    } else {
        sw_col = col;
        sw_row = row;
    }

    if ( sw_row == 1 && sw_col == 1 ) {
        kings = 0;
    } else {
        if ( sw_row == 1 ) {
            rows_with_blanks = 1;
            rows_filled = 0;
        } else {
            rows_with_blanks = sw_row / 2;
            rows_filled = sw_row / 2 + sw_row % 2;
        }
        kings = calculate_kings( rows_with_blanks, rows_filled, sw_col );
    }

    cout << kings << endl;

    return 0;
}

uint32_t calculate_kings( uint32_t rows_with_blanks, uint32_t rows_filled, uint32_t sw_col ) {
    uint32_t kings_in_blank_rows;
    uint32_t blanks;
    uint32_t kings;

    blanks = sw_col / 3 + ( sw_col % 3 ? 1 : 0 );
    kings_in_blank_rows = sw_col - blanks;

    kings = rows_filled * sw_col + rows_with_blanks * kings_in_blank_rows;
    return kings;
}
