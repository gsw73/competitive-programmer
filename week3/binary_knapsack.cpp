//
// Created by Gregory Walter on 5/12/20.
//
// INPUT
// Line 1:  n, w such that (1 ≤ n ≤ 100, 0 ≤ w ≤ 2^30):  number of items and maximum weight in knapsack
// Line 2 - Line n + 1:  wi, vi (1 ≤ wi ≤ 2^30, 0 ≤ vi ≤ 10^6), the weight and value of the ith item
//          in the set.  Each wi is a power of 2.

#include <iostream>
#include <vector>
#include <cinttypes>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

#define MYDEBUG

class Item {
private:
    uint32_t weight;
    uint32_t value;
public:
    Item();
    explicit Item(uint32_t w, uint32_t v);
    uint32_t get_weight() const { return weight; }
    uint32_t get_value() const { return value; }
    friend std::ostream & operator<<(std::ostream & os, const Item & it);
    friend bool operator<(const Item & i1, const Item & i2);
};

Item::Item() {
    weight = 0;
    value = 0;
}

Item::Item(uint32_t w, uint32_t v) {
    weight = w;
    value = v;
}

std::ostream & operator<<(std::ostream & os, const Item & it) {
    os << "w = " << it.weight << ", v = " << it.value;
    return os;
}

bool operator<(const Item & i1, const Item & i2 ) {
    if ((i1.value > i2.value) || ((i1.value == i2.value) && (i1.weight < i2.weight)))
        return true;
    else
        return false;
}

static uint32_t calls;
static uint32_t max_value;
void show_input( uint32_t, uint32_t, vector<Item> & );
void save_max_value(uint32_t);
void fill_knapsack(uint32_t cumulative_weight, uint32_t cumulative_value, uint32_t wmax, uint32_t start, vector<Item> & items);

int main( int argc, char *argv[] ) {
    uint32_t n, wmax;
    vector<Item> items;

    cin >> n >> wmax;
    for ( int i = 0; i < n; i++ ) {
        uint32_t wi, vi;
        cin >> wi >> vi;
        Item *an_item = new Item(wi, vi);
        items.push_back(*an_item);
    }
    
    show_input( n, wmax, items );

    std::sort(items.begin(), items.end());

    cout << endl;
    cout << "sorted by high value:  " << endl;
    show_input( n, wmax, items );

    fill_knapsack(0, 0, wmax, 0, items);

    cout << "max value is" << endl;
    cout << max_value << endl;
    return 0;
}

void fill_knapsack(uint32_t cumulative_weight, uint32_t cumulative_value, uint32_t wmax, uint32_t start, vector<Item> & items) {
    uint32_t cw, cv;
    uint32_t next_start;

    calls++;
    for ( int j = 0; j < start; j++ ) { cout << "\t"; }
    cout << "Call" << calls << " with w=" << cumulative_weight << ", v=" << cumulative_value << ", start=" << start << endl;

    for ( int i = start; i < items.size(); i++) {
        cw = cumulative_weight + items[i].get_weight();
        cv = cumulative_value + items[i].get_value();
        next_start = i + 1;

        if (cw > wmax) {
            cout << "Exceeded wmax, cw=" << cw << ", cv=" << cv << endl;
            continue;
        } else if (cw == wmax) {
            cout << "At wmax, cw=" << cw << ", cv=" << cv << endl;
            save_max_value(cv);
        } else
            fill_knapsack(cw, cv, wmax, next_start, items);
    }
    save_max_value(cumulative_value);
}

void save_max_value( uint32_t cv) {
    // cout << "\tCheck max value, max_value=" << max_value << ", cv=" << cv << endl;
    if (cv > max_value)
        max_value = cv;
}

void show_input( uint32_t n, uint32_t wmax, vector<Item> & items ) {
    cout << "n = " << n << ", wmax = " << wmax << endl;
    for ( auto & val : items )
        cout << val << endl;
}

