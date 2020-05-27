//
// Created by Gregory Walter on 5/26/20.
//

// INPUT:
// Line1: n, m (1 ≤ n, m ≤ 1000); lengths of u and w, respectively
// Line2: string u
// Line3: string w
// Line4: three integers, I, D, and S (1 ≤ I, D, S ≤ 100), the cost of insertion,
// deletion, and substitution

#include <iostream>
#include <cinttypes>
#include <array>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// #define MYDEBUG

void show_input(uint32_t n, uint32_t m, string &u, string &w, uint32_t i, uint32_t d, uint32_t s_c);
void show_matrix(uint32_t **myarray, uint32_t n, uint32_t m);
uint32_t mymin(uint32_t d, uint32_t i, uint32_t s);

int main(int argc, char *argv[]) {
    uint32_t n_len_u, m_len_w;
    string u_str, w_str;
    uint32_t i_cost, d_cost, s_cost;
    uint32_t **ar;

    cin >> n_len_u >> m_len_w;
    cin >> u_str >> w_str;
    cin >> i_cost >> d_cost >> s_cost;

#ifdef MYDEBUG
    show_input(n_len_u, m_len_w, u_str, w_str, i_cost, d_cost, s_cost);
#endif

    // allocate space for 2d array
    ar = new uint32_t* [n_len_u + 1];
    auto tmp_p = ar;
    for (int32_t i = 0; i < n_len_u + 1; ++i) {
        *tmp_p++ = new uint32_t [m_len_w + 1];
    }

    // initialize entire array to a really big number
    for (int32_t i = 0; i < n_len_u + 1; ++i) {
        for (int32_t j = 0; j < m_len_w + 1; ++j) {
            ar[i][j] = (uint32_t) -2;
        }
    }

    // initialize first row - inserting
    for (int32_t i = 0; i < m_len_w + 1; ++i){
        ar[0][i] = (uint32_t) i * i_cost;
    }

    // initialize first column - deleting
    for (int32_t i = 0; i < n_len_u + 1; ++i) {
        ar[i][0] = (uint32_t) i * d_cost;
    }

#ifdef MYDEBUG
    show_matrix(ar, n_len_u, m_len_w);
#endif

    // implement the distance algorithm
    for ( auto i = 1; i < n_len_u + 1; ++i) {
        for ( auto j = 1; j < m_len_w + 1; ++j) {
            auto diff = u_str[i - 1] == w_str[j - 1] ? 0 : s_cost;
            auto del = ar[i - 1][j] + d_cost;
            auto ins = ar[i][j - 1] + i_cost;
            auto sub = ar[i - 1][j - 1] + diff;
            ar[i][j] = mymin(del, ins, sub);
        }
    }

#ifdef MYDEBUG
    cout << endl << endl;
    show_matrix(ar, n_len_u, m_len_w);
    cout << endl << endl;

    cout << "edit distance = " << endl;
#endif

    cout << ar[n_len_u][m_len_w] << endl;

    return 0;
}

uint32_t mymin(uint32_t d, uint32_t i, uint32_t s) {
    uint32_t min;
    min = d;
    min = i < min ? i : min;
    min = s < min ? s : min;
    return(min);
}

void show_matrix(uint32_t **myarray, uint32_t n, uint32_t m) {
    for (int32_t i = 0; i < n + 1; ++i){
        for (int32_t j = 0; j < m + 1; ++j) {
            printf("0x%08x ", myarray[i][j]);
        }
        cout << endl;
    }
}

void show_input(uint32_t n, uint32_t m, string &u, string &w, uint32_t i, uint32_t d, uint32_t s_c) {
    cout << "n=" << n << " m=" << m << endl;
    cout << "u=" << u << " w=" << w << endl;
    cout << "i=" << i << " d=" << d << " s=" << s_c << endl;
}


