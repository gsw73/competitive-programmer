//
// Created by Gregory Walter on 5/10/20.
//

#include <iostream>
#include <cinttypes>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

// #define MYDEBUG

int main( int argc, char *argv[] ) {
    int32_t x, y, rounded;
    div_t ans;

    cin >> x >> y;
    ans = div(x, y);

#ifdef MYDEBUG
    cout << "x=" << x << ", y=" << y << endl;
    cout << "quot=" << ans.quot << ", rem= " << ans.rem << endl;
#endif

    if ( ans.quot < 0 ) {
        rounded = ans.quot;
    } else if ( ans.quot == 0 ) {
        if ( ans.rem == 0 ) {
            rounded = ans.quot;
        } else if ( ( x < 0 && y < 0 ) || ( x > 0 && y > 0 ) ) {
            rounded = 1;
        } else {
            rounded = 0;
        }
    } else {
        // ans.quot > 0
        if ( ans.rem == 0 )
            rounded = ans.quot;
        else
            rounded = ans.quot + 1;
    }

    cout << rounded << endl;

    return 0;
}
