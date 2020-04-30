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
unsigned int method_three();

int main( int argc, char *argv[] ) {
    unsigned int length;
    int method;

    if ( argc == 2 ) {
        method = std::strtol(argv[1], NULL, 10);
    }

    if ( argc == 1 || ( argc == 2 && method == 1 ) ) {
        length = method_one();
    } else if ( argc == 2 && method == 2 ){
        length = method_two();
    } else if ( argc == 2 && method == 3 ) {
        length = method_three();
    } else {
        cout << "ERROR: bad argc of" << argc << endl;
        cout << "]$ increment [1|2|3]";
        return -1;
    }

    cout << length << endl;

    return 0;
}

unsigned int method_one() {
    string val_st;
    unsigned int len;
    unsigned int xp1_len;
    bool all_nines = true;

    // read entire string from standard input
    cin >> val_st;

    // are all characters '9'?
    for (auto val : val_st) {
        if (val != '9') {
            all_nines = false;
            break;
        }
    }

    // original string length
    len = val_st.length();

#ifdef MYDEBUG
    cout << "Method 1 (C++ string)" << endl;
    cout << "length = " << len << endl;
    cout << "all 9s? " << std::boolalpha << all_nines << endl;
#endif

    xp1_len = all_nines ? len + 1 : len;

    return xp1_len;
}

unsigned int method_two() {
    unsigned int len = 0;
    unsigned int xp1_len;
    char char_digit;
    bool all_nines = true;

    // read value from standard input
    while( cin.get(char_digit) ) {
        if (std::isdigit(char_digit)) {
            len++;
            if ( char_digit != '9' ) {
                all_nines = false;
            }
        } else if ( char_digit == '\n' ) {
            break;
        }
    }

#ifdef MYDEBUG
    cout << "Method 2 (cin.get(char&)" << endl;
    cout << "length = " << len << endl;
    cout << "all 9s? " << std::boolalpha << all_nines << endl;
#endif

    xp1_len = all_nines ? len + 1 : len;

    return xp1_len;
}

unsigned int method_three() {
    const int MAXCHAR = 1000000 + 3;
    char big_str[MAXCHAR];
    unsigned int len = 0;
    unsigned int xp1_len;
    char *tmp_p = big_str;
    bool all_nines = true;

    // read entire line from stdin
    cin.getline(big_str, MAXCHAR);

    // count digits
    while(*tmp_p != '\0') {
        if ( isdigit(*tmp_p) ) {
            len++;
            if ( *tmp_p != '9' ) {
                all_nines = false;
            }
        }
        tmp_p++;
    }

#ifdef MYDEBUG
    cout << "Method 3 (getline)" << endl;
    cout << "input string = " << big_str << endl;
    cout << "length = " << len << endl;
    cout << "all 9s? " << std::boolalpha << all_nines << endl;
#endif

    xp1_len = all_nines ? len + 1 : len;

    return xp1_len;
}
