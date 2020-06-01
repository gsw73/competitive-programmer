//
// Created by Gregory Walter on 5/30/20.
//

#include <iostream>
#include <cinttypes>
#include <array>

using std::cin;
using std::cout;
using std::endl;
using std::array;

// #define MYDEBUG
static const uint32_t method = 1;
static const uint32_t LMAX = 18 + 1; // count 1 to 18
static const uint32_t SMAX = 162 + 1; // count 0 to 162
static array<array<int64_t, LMAX>, SMAX> ar;

int64_t calc(int32_t, uint32_t);
int64_t iterative_method(int32_t sum, int32_t length);
int32_t end_check(int32_t s);

int main(int argc, char *argv[]) {
    uint32_t length;
    int32_t sum;
    int64_t total = 0;
    int64_t subtotal;

    // init global array
    for (auto row = 0; row < SMAX; ++row) {
        for (auto col = 0; col < LMAX; ++col) {
            ar.at(row).at(col) = -1;
        }
    }

    cin >> sum >> length;

#ifdef MYDEBUG
    cout << "S = " << sum << ", L = " << length << endl;
#endif

    if (method == 2) {
        total = iterative_method(sum, length);
        cout << total << endl;
        return 0;
    }

    // last element
    // cout << ar.at(162).at(18) << endl;

    if (length == 1) {
        total = sum <= 9 ? 1 : 0;
    } else if (sum == 0) {
        total = 0;
    } else {
        for (int32_t d1 = 1; d1 <= 9; ++d1) {
            subtotal = calc(sum - d1, length - 1);
            total += subtotal;
        }
    }

    cout << total << endl;

    return 0;
}

int64_t calc(int32_t S, uint32_t L) {
    int64_t total = 0;
    int64_t subtotal;
    int64_t val;
    int32_t next_s;
    uint32_t next_l;

    if (L == 1) {
        int64_t t = (S <= 9) && (S>=0) ? 1 : 0;
        return t;
    }

    for (auto d = 0; d <= 9; ++d) {
        next_s = S - d;
        next_l = L - 1;

        // don't lookup invalid indices
        if (next_s < 0) {
            continue;
        }

        val = ar.at(next_s).at(next_l);
        if (val != -1) {
            subtotal = val;
            total += subtotal;
        } else {
            subtotal = calc(next_s, next_l);
            total += subtotal;
            ar.at(next_s).at(next_l) = subtotal;
        }
    }
    return total;
}

static const int32_t LEVELS = 18;

int32_t end_check(int32_t s) {
    int32_t vld;
    if ((s <= 9) && (s >= 0)) {
        vld = 1;
    } else {
        vld = 0;
    }
    return vld;
}

// FIXME:  doesn't have lookup implemented and only goes to L = 10; more of a study
int64_t iterative_method(int32_t sum, int32_t length) {
    int64_t total = 0;
    int64_t subtotal;
    int32_t s[LEVELS + 1]{0};
    int32_t l[LEVELS + 1]{0};

    s[1] = sum;
    l[1] = length;

    if (length == 1) {
        total = s[1] <= 9 ? 1 : 0;
    } else if (s[1] == 0) {
        total = 0;
    } else {
        for(auto d1 = 1; d1 <= 9; ++d1) {
            s[2] = s[1] - d1;
            l[2] = l[1] - 1;
            if (l[2] == 1) {
                subtotal = end_check(s[2]);
                total += subtotal;
            } else {
                for(auto d2 = 0; d2 <= 9; ++d2) {
                    s[3] = s[2] - d2;
                    l[3] = l[2] - 1;
                    if(l[3] == 1) {
                        subtotal = end_check(s[3]);
                        total+=subtotal;
                    } else {
                        for(auto d3 = 0; d3 <= 9; ++d3) {
                            s[4] = s[3] - d3;
                            l[4] = l[3] - 1;
                            if (l[4] == 1) {
                                subtotal = end_check(s[4]);
                                total += subtotal;
                            } else {
                                for(auto d4 = 0; d4 <= 9; ++d4) {
                                    s[5] = s[4] - d4;
                                    l[5] = l[4] - 1;
                                    if (l[5] == 1) {
                                        subtotal = end_check(s[5]);
                                        total += subtotal;
                                    } else {
                                        for (auto d5 = 0; d5 <= 9; ++d5) {
                                            s[6] = s[5] - d5;
                                            l[6] = l[5] - 1;
                                            if (l[6] == 1) {
                                                subtotal = end_check(s[6]);
                                                total += subtotal;
                                            } else {
                                                for (auto d6 = 0; d6 <= 9; ++d6) {
                                                    s[7] = s[6] - d6;
                                                    l[7] = l[6] - 1;
                                                    if (l[7] == 1) {
                                                        subtotal = end_check(s[7]);
                                                        total += subtotal;
                                                    } else {
                                                        for (auto d7 = 0; d7 <= 9; ++d7) {
                                                            s[8] = s[7] - d7;
                                                            l[8] = l[7] - 1;
                                                            if (l[8] == 1) {
                                                                subtotal = end_check(s[8]);
                                                                total += subtotal;
                                                            } else {
                                                                for (auto d8 = 0; d8 <= 9; ++d8) {
                                                                    s[9] = s[8] - d8;
                                                                    l[9] = l[8] - 1;
                                                                    if (l[9] == 1) {
                                                                        subtotal = end_check(s[9]);
                                                                        total += subtotal;
                                                                    } else {
                                                                        for (auto d9 = 0; d9 <= 9; ++d9) {
                                                                            s[10] = s[9] - d9;
                                                                            l[10] = l[9] - 1;
                                                                            if (l[10] == 1) {
                                                                                subtotal = end_check(s[10]);
                                                                                total += subtotal;
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return total;
}

