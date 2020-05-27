//
// Created by Gregory Walter on 5/27/20.
//

// INPUT
// Line1: n (1 ≤ n ≤ 2000), the number of elements in A
// Line2: A[1], A[2], ..., A[n] (1 ≤ A[i] ≤ 1,000,000)
// OUTPUT
// The length of the longest increasing subsequence

#include <iostream>
#include <cinttypes>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// #define MYDEBUG

void show_input(uint32_t, vector<uint32_t> &);

int main(int argc, char *argv[]) {
    uint32_t num;
    vector<uint32_t> ar;
    vector<uint32_t> t_ar;

    cin >> num;
    for (auto i = 0; i < num; i++) {
        uint32_t val;
        cin >> val;
        ar.push_back(val);
    }

#ifdef MYDEBUG
    show_input(num, ar);
#endif

    // implement algorithm
    for (auto i = 0; i < ar.size(); ++i){
        t_ar.push_back(1);
        for (auto j = 0; j < i; ++j) {
            if ( (ar.at(j) < ar.at(i)) && t_ar.at(i) < t_ar.at(j) + 1) {
                t_ar.at(i) = t_ar.at(j) + 1;
            }
        }
    }

    auto LIS = std::max_element(t_ar.begin(), t_ar.end());
    cout << *LIS << endl;

    return 0;
}

void show_input(uint32_t n, vector<uint32_t> &A) {
    cout << n << endl;
    for (auto val: A) {cout << val << " ";}
    cout << endl;
}

