//
// Created by Gregory Walter on 4/26/20.
//

// Given non-negative integer, x, find number of decimal digits in x + 1
// Input:  x (0 <= x <= 10^1000000)
// Output:  decimal digits in x + 1

#include <iostream>
#include <string>

// #define MYDEBUG

int main( int argc, char *argv[] ) {
    using namespace std;

    string val_st;
    unsigned int len;
    unsigned int xp1_len;

    // read value from standard input
    cin >> val_st;

    len = val_st.length();

#ifdef MYDEBUG
    cout << "length = " << len << endl;
    cout << "final digit = " << val_st[len - 1] << endl;
#endif

    xp1_len = val_st[len-1] == '9' ? len + 1 : len;
    cout << xp1_len;

    return 0;
}
