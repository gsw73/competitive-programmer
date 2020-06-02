//
// Created by Gregory Walter on 6/2/20.
//

// INPUT:
// LINE1:  n, W (1 ≤ n ≤ 100, 0 ≤ W ≤ 1000), the number of items and max total weight
// LINE2 - LINE(n+1):  w_i, v_i (1 ≤ w_i ≤ 1000, 0 ≤ v_i ≤ 1000)

#include <iostream>
#include <vector>
#include <cinttypes>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::reverse;

// #define MYDEBUG

struct item { uint32_t w; uint32_t v; };

void show_input(uint32_t, uint32_t, vector<item>&);
void show_table(uint32_t, uint32_t, vector<vector<int32_t>>&);
inline int32_t mymax(int32_t, int32_t);

int main(int argc, char *argv[]) {
    uint32_t num, w_max;
    vector<item> items;
    vector<vector<int32_t>> Ti;
    vector<int32_t> vertices;

    cin >> num >> w_max;
    for (auto i = 0; i < num; ++i) {
        item new_item{0};
        cin >> new_item.w >> new_item.v;
        items.push_back(new_item);
    }

#ifdef MYDEBUG
    show_input(num, w_max, items);
#endif

    // initialize table to None, going down
    for (auto i = 0; i < w_max + 1; ++i) {
        vector<int32_t> v_row(num + 1, -1);
        Ti.push_back(v_row);
    }

#ifdef MYDEBUG
    show_table(num, w_max, Ti);
#endif

    // init the no-items col to 0
    for (auto row = 0; row < w_max + 1; ++row) {
        Ti.at(row).at(0) = 0;
    }

#ifdef MYDEBUG
    cout << endl;
    show_table(num, w_max, Ti);
#endif

    // go down each column, filling in the table, starting at col1
    // col = item number, i;
    // row = current weight, u;
    for (auto col = 1; col < num + 1; ++col) {
        for (auto row = 0; row < w_max + 1; ++row) {
            // init the square with the prev col
            Ti.at(row).at(col) = Ti.at(row).at(col - 1);

            // if the next item can fit in the bag, see if it adds value
            item item_to_check = items.at(col - 1);
            if (row >= item_to_check.w) {
                Ti.at(row).at(col) = mymax(Ti.at(row).at(col), Ti.at(row - item_to_check.w).at(col - 1) + item_to_check.v);
            }
        }
    }

#ifdef MYDEBUG
    cout << endl;
    show_table(num, w_max, Ti);
    cout << "max value=" << Ti.at(w_max).at(num) << endl;
#endif


    // unwind
    uint32_t row = w_max;
    for (auto col = num; col >= 1; --col) {
        if (Ti.at(row).at(col) == Ti.at(row).at(col - 1)) {
            continue;
        } else {
            vertices.push_back(col - 1);
            row -= items.at(col - 1).w;
        }
    }

    // put vertices in incrementing order
    reverse(vertices.begin(), vertices.end());

#ifdef MYDEBUG
    cout << "k= first row; vertices = second row" << endl;
    cout << "vertices = " << endl;
#endif

    // answer requires 1-based vertices i.e., from 1 to n; vertices is 0 based, so add 1 here
    cout << vertices.size() << endl;
    for (auto val : vertices) { cout << val + 1 << " "; }

    return 0;
}

int32_t mymax(int32_t a, int32_t b) {
    if (a > b)
        return a;
    else
        return b;
}

void show_table(uint32_t n, uint32_t W, vector<vector<int32_t>> &T) {
    for(auto row = 0; row < W + 1; ++row) {
        printf("%3d:", row);
        for(auto col = 0; col < n + 1; ++col ) {
            printf("%3d ", T.at(row).at(col));
        }
        cout << endl;
    }
}

void show_input(uint32_t n, uint32_t W, vector<item> &all_items) {
    int32_t i = 0;
    cout << "n=" << n << " W=" << W << endl;
    for ( auto val : all_items) {
        cout << i << ":  w=" << val.w << " v=" << val.v << endl;
        i++;
    }
}
