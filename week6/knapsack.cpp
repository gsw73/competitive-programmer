//
// Created by Gregory Walter on 6/2/20.
//

// INPUT:
// LINE1:  n, W (1 ≤ n ≤ 100, 0 ≤ W ≤ 1000), the number of items and max total weight
// LINE2 - LINE(n+1):  w_i, v_i (1 ≤ w_i ≤ 1000, 0 ≤ v_i ≤ 1000)

#include <iostream>
#include <vector>
#include <cinttypes>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

#define MYDEBUG

struct item { uint32_t w; uint32_t v; };

void show_input(uint32_t, uint32_t, vector<item>&);
void show_table(uint32_t, uint32_t, vector<vector<int32_t>>&);
inline int32_t mymax(int32_t, int32_t);

int main(int argc, char *argv[]) {
    uint32_t num, w_max;
    vector<item> items;
    vector<vector<int32_t>> Ti;

    cin >> num >> w_max;
    for (auto i = 0; i < num; ++i) {
        item new_item{0};
        cin >> new_item.w >> new_item.v;
        items.push_back(new_item);
    }

    show_input(num, w_max, items);

    // initialize table to None, going down
    for (auto i = 0; i < w_max + 1; ++i) {
        vector<int32_t> v_row(num + 1, -1);
        Ti.push_back(v_row);
    }

    show_table(num, w_max, Ti);

    // init the no-items col to 0
    for (auto row = 0; row < w_max + 1; ++row) {
        Ti.at(row).at(0) = 0;
    }

    cout << endl;
    show_table(num, w_max, Ti);

    // go down each column, filling in the table, starting at col1
    // col = item number, i;
    // row = current weight, u;
    for (auto col = 1; col < num + 1; ++col) {
        for (auto row = 0; row < w_max + 1; ++row) {
            // init the square with the prev col
            Ti.at(row).at(col) = Ti.at(row).at(col - 1);

            // if the next item can fit in the bag, see if it adds value
            if (row >= items.at(col - 1).w) {
                item item_to_check = items.at(col - 1);
                Ti.at(row).at(col) = mymax(Ti.at(row).at(col), Ti.at(row - item_to_check.w).at(col - 1) + item_to_check.v);
            }
        }
    }

    cout << endl;
    show_table(num, w_max, Ti);

    cout << "max value=" << Ti.at(w_max).at(num) << endl;

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
