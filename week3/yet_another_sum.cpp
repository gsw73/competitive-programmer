//
// Created by Gregory Walter on 5/11/20.
//

// sequence of integers x1, x2, ..., xn, compute the sum
// s = ∑ i = 1 to i = n (xi + 1/xi)
// result should be a double
// INPUT
// Line 1:  n (1 ≤ n ≤ 50), the length of the sequence
// Line 2:  integers x1, x2, ..., xn (-10^9 ≤ xi ≤ 10^9, xi ≠ 0)
// OUTPUT
// floating-point number, s, with absolute or relative error not exceeding 10^-9

#include <iostream>
#include <cinttypes>
#include <vector>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// #define MYDEBUG

void show_input( int32_t, vector<int32_t> & );

int main( int argc, char *argv[] ) {
    int32_t n;
    int32_t x_val;
    vector<int32_t> vec_x;
    int64_t sum_a = 0;
    double sum_b = 0.0;
    double inverted;
    double sum;

    cin >> n;

    for ( int i = 0; i < n; i++ ) {
        cin >> x_val;
        vec_x.push_back( x_val );
    }

#ifdef MYDEBUG
    show_input( n, vec_x );
#endif

    // sum = SUM { i = 1 to i = n, (xi) } + SUM { i = 1 to i = n, (xi)^-1 }
    for ( auto & val : vec_x ) {
        sum_a += val;
        inverted = 1.0/val;
#ifdef MYDEBUG
        cout << std::fixed << std::setprecision( 20 );
        cout << "inverted = " << inverted << endl;
#endif
        sum_b += inverted;
    }
    sum = sum_a + sum_b;

#ifdef MYDEBUG
    cout << std::fixed << std::setprecision( 20 );
    cout << "sum_a = " << sum_a << endl;
    cout << "sum_b = " << sum_b << endl;
#endif
    cout << std::fixed << std::setprecision( 10 );
    cout << sum << endl;

    return 0;
}

void show_input( int32_t n, vector<int32_t> & vec ) {
    cout << n << endl;

    for ( auto & val : vec ) {
        cout << val << " ";
    }
    cout << endl;
}

