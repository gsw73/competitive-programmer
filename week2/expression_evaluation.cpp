//
// Created by Gregory Walter on 5/5/20.
//
// s, non-empty string containing only digits and symbols + and -; length
// of s does not exceed 50000
//
// Ex:  1+2+3+4
// stdout:  10
// Ex:  1-2+3-4
// stdout: -2

#include <iostream>
#include <cinttypes>

using std::cin;
using std::cout;
using std::endl;

int main( int argc, char *argv[] ) {
    int64_t result = 0;
    int32_t val;

    while( cin >> val ) {
        result += val;
    }

    cout << result << endl;

    return 0;
}


