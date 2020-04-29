//
// Created by Gregory Walter on 4/26/20.
//

// Given non-negative integer, x, find number of decimal digits in x + 1
// Input:  x (0 <= x <= 10^1000000)
// Output:  decimal digits in x + 1
//
// Two methods:
// Call memory-intensive with no arguments
// ]$ increment
// Call time-intensive with 1 argument
// ]$ increment 1

#include <iostream>
#include <string>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// #define MYDEBUG

unsigned int method_one();
unsigned int method_two();

int main( int argc, char *argv[] ) {
    unsigned int length;

    if ( argc == 1 ) {
        length = method_two();
    } else {
        length = method_one();
    }

    cout << length << endl;

    return 0;
}

unsigned int method_one() {
    string val_st;
    unsigned int len;
    unsigned int xp1_len;

    // read entire string from standard input
    cin >> val_st;

    // get length
    len = val_st.length();

#ifdef MYDEBUG
    cout << "Method 1 (memory intensive)" << endl;
    cout << "length = " << len << endl;
    cout << "final digit = " << val_st[len - 1] << endl;
#endif

    xp1_len = val_st[len-1] == '9' ? len + 1 : len;

    return xp1_len;
}

unsigned int method_two() {
    unsigned int len = 0;
    unsigned int xp1_len;
    char char_digit;
    char final_char_digit = 0;

    // read value from standard input
    while( cin.get(char_digit) ) {
        if (std::isspace(char_digit)) break;
        final_char_digit = char_digit;
        len++;
    }

#ifdef MYDEBUG
    cout << "Method 2 (time intensive)" << endl;
    cout << "length = " << len << endl;
    cout << "final digit = " << final_char_digit << endl;
#endif

    xp1_len = final_char_digit == '9' ? len + 1 : len;

    return xp1_len;
}
