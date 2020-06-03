//
// Created by Gregory Walter on 6/3/20.
//

// INPUT
// Line1: integer n (2 ≤ n ≤ 150), the number of matrices to be multiplied
// Line2: (n + 1) integers m_0, m_1, ..., m_n (1 ≤ m_i ≤ 1000) the size of the i-th
// matrix is m_i x m_(i+1)
// OUTPUT
// minimum cost of multiplying the given n matrices

#include <iostream>
#include <vector>
#include <cinttypes>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// #define MYDEBUG

vector<vector<int64_t>> Tr;

void show_input(uint32_t, vector<uint32_t> &);
void show_table(uint32_t);
int64_t matrix_mult(vector<uint32_t> &, uint32_t, uint32_t);
inline int64_t my_min(int64_t a, int64_t b) {
    if ( a < b )
        return a;
    else
        return b;
}

int main(int argc, char *argv[]) {
    uint32_t num;
    vector<uint32_t> m_sizes;
    int64_t mmc;

    // read in problem input data
    cin >> num;
    for (auto i = 0; i < num + 1; ++i) {
        uint32_t m;
        cin >> m;
        m_sizes.push_back(m);
    }

#ifdef MYDEBUG
    show_input(num, m_sizes);
#endif

    // create table, (n+1)x(n+1), to hold minimum matrix multiplications for each call
    for (auto row = 0; row < num + 1; ++row) {
        vector<int64_t>r(num + 1, -1);
        Tr.push_back(r);
    }

    mmc = matrix_mult(m_sizes, 0, num);

#ifdef MYDEBUG
    cout << endl;
    show_table(num);
#endif

    cout << mmc << endl;

    return 0;
}

int64_t matrix_mult(vector<uint32_t> &ms, uint32_t i, uint32_t j) {
    if (Tr.at(i).at(j) == -1) {
        if (j == i + 1) {
            Tr.at(i).at(j) = 0;
        } else {
            Tr.at(i).at(j) = (int64_t) 0x7fffffffffffffffL;
            for (auto k = i + 1; k < j; ++k) {
                Tr.at(i).at(j) = my_min(Tr.at(i).at(j), matrix_mult(ms, i, k) + matrix_mult(ms, k, j) + ms[i] * ms[j] * ms[k]);
            }
        }
    }
    return Tr.at(i).at(j);
}

void show_table(uint32_t n) {
    for (auto row = 0; row < n + 1; ++row) {
        for (auto col = 0; col < n + 1; ++col) {
            // printf("%3ld ", Tr.at(row).at(col));
            cout.width(4);
            cout << Tr.at(row).at(col) << " ";
        }
        cout << endl;
    }
}

void show_input(uint32_t n, vector<uint32_t> &ms) {
    cout << n << endl;
    for (auto val : ms) {cout << val << " ";}
    cout << endl;
}
