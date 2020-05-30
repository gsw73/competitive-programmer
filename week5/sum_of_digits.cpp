//
// Created by Gregory Walter on 5/30/20.
//

#include <iostream>
#include <cinttypes>

using std::cin;
using std::cout;
using std::endl;

int32_t calc(int32_t, uint32_t);

inline int32_t min(int32_t a, int32_t b) {
    int32_t m = a < b ? a : b;
    return m;
}

inline int32_t max(int32_t a, int32_t b) {
    int32_t m = a > b ? a : b;
    return m;
}

int main(int argc, char *argv[]) {
    uint32_t length;
    int32_t sum;
    uint32_t total = 0;

    cin >> sum >> length;

    cout << "S = " << sum << ", L = " << length << endl;

    if (length == 1) {
        total = sum <= 9 ? 1 : 0;
    } else {
        for (int32_t d1 = 1; d1 <= min(sum, 9) && length > 1; ++d1) {
            total += calc(sum - d1, length - 1);
        }
    }

    cout << total << endl;

    return 0;
}

int32_t calc(int32_t S, uint32_t L) {
    uint32_t total = 0;

    if (L == 1) {
        int32_t t = S <= 9 ? 1 : 0;
        return t;
    }

    // for (auto d = max(0,S - 9); d <= min(S, 9); ++d) {
    for (auto d = max(0, min(9, S - 9)); d <= min(S, 9); ++d) {
        total += calc(S - d, L - 1);
    }

    return total;
}

