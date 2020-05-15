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
#include <array>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::array;
using std::sort;
using std::reverse;

// #define MYDEBUG

class Item {
private:
    uint32_t weight;
    uint32_t value;
public:
    Item();

    explicit Item(uint32_t w, uint32_t v);

    uint32_t get_weight() const { return weight; }

    uint32_t get_value() const { return value; }

    friend std::ostream &operator<<(std::ostream &os, const Item &it);

    friend bool operator<(const Item &i1, const Item &i2);
};

Item::Item() {
    weight = 0;
    value = 0;
}

Item::Item(uint32_t w, uint32_t v) {
    weight = w;
    value = v;
}

std::ostream &operator<<(std::ostream &os, const Item &it) {
    os << "w = " << it.weight << ", v = " << it.value;
    return os;
}

bool operator<(const Item &i1, const Item &i2) {
    return (i1.weight < i2.weight) || ((i1.weight == i2.weight) && (i1.value < i2.value));
}

void show_input(uint32_t, uint32_t, vector<Item> &);

int main(int argc, char *argv[]) {
    uint32_t n, wmax;
    vector<Item> items;
    uint32_t max_value = 0;
    array<uint32_t, 32> sub_bags{0};
    array<uint32_t, 100> same_weight_values{0};
    array<uint32_t, 100> doubled_same_weight_values{0};
    uint32_t sub_bag_weight;
    uint32_t swv_size = 0;
    uint32_t dswv_size = 0;
    uint32_t combined_value;


    cin >> n >> wmax;
    for (int i = 0; i < n; i++) {
        uint32_t wi, vi;
        cin >> wi >> vi;
        Item *an_item = new Item(wi, vi);
        items.push_back(*an_item);
    }

#ifdef MYDEBUG
    show_input(n, wmax, items);
#endif

    // items are sorted with lightest weight at the back
    sort(items.begin(), items.end());
    reverse(items.begin(), items.end());

#ifdef MYDEBUG
    cout << endl;
    cout << "sorted by high weight:  " << endl;
    show_input(n, wmax, items);
#endif

    for (uint32_t i = 0; i < 31; i++) {
        sub_bag_weight = 1U << i;
        while (!items.empty() && items.back().get_weight() == sub_bag_weight) {
            same_weight_values[swv_size] = items.back().get_value();
            swv_size++;
            items.pop_back();
        }

        // array holds list of all values that fit in the same size bags;
        // sort array so most valuable is at the end
        sort(same_weight_values.begin(), same_weight_values.begin() + swv_size);

        // if wmax has a sub bag of this size, take highest value (last element) and put it in the bag
        if ((wmax & sub_bag_weight) && (swv_size > 0)) {
            sub_bags[i] = same_weight_values[swv_size - 1];
            same_weight_values[swv_size - 1] = 0;
            swv_size--;
        }

        // double up as many elements as possible--each will fit in a bag twice its size; any
        // leftover element will also fit in a bag twice its size
        while (swv_size >= 2) {
            combined_value = same_weight_values[swv_size - 1] + same_weight_values[swv_size - 2];
            same_weight_values[swv_size - 1] = 0;
            same_weight_values[swv_size - 2] = 0;
            swv_size -= 2;
            doubled_same_weight_values[dswv_size] = combined_value;
            dswv_size++;
        }

        assert(swv_size == 0 || swv_size == 1);

        // pick up any stray value and combine it with nothing--it also fits in a larger bag
        if (swv_size) {
            doubled_same_weight_values[dswv_size] = same_weight_values[swv_size - 1];
            dswv_size++;
            same_weight_values[swv_size - 1] = 0;
            swv_size--;
        }

        assert(swv_size == 0);

        // re-init bags to start process over
        same_weight_values = doubled_same_weight_values;
        swv_size = dswv_size;
        doubled_same_weight_values.fill(0);
        dswv_size = 0;
    }

    // max value is the sum of the maximum value that could be fitted into each sub bag
    for (auto &val : sub_bags) max_value += val;

    cout << max_value << endl;
    return 0;
}

void show_input(uint32_t n, uint32_t wmax, vector<Item> &items) {
    cout << "n = " << n << ", wmax = " << wmax << endl;
    for (auto &val : items)
        cout << val << endl;
}

