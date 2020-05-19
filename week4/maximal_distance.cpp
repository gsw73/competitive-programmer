//
// Created by Gregory Walter on 5/19/20.
//

// INPUT:
// Line 1:  integer n (1 ≤ n ≤ 100,000), the number of points on a line
// Line 2 to Line n+1:  coordinate x_i of the i-th point (0 ≤ x_i ≤ 10^9), an integer; all points are different
// OUTPUT:
// Print n lines, i-th line contains two numbers f_i and s_i (1 ≤ f_i, s_i ≤ i), the indices of
// two points with max distance among first i points

#include <iostream>
#include <cinttypes>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

struct coord {
    uint32_t ind;
    uint32_t location;
};

struct pair {
    uint32_t index_min;
    uint32_t index_max;
};

int main(int argc, char *argv[]) {
    uint32_t n;
    vector<uint32_t> coordinates;
    coord min{0};
    coord max{0};
    vector<pair> answer;

    cin >> n;

    // don't use location 0 - coordinates are numbered from 1
    coordinates.push_back(0);
    for (uint32_t i = 0; i < n; i++) {
        uint32_t val;
        cin >> val;
        coordinates.push_back(val);
    }

    // seed min and max with first coordinate since the first answer is always "1 1"
    min = {1, coordinates[1]};
    max = {1, coordinates[1]};
    answer.push_back({1, 1});

    for (uint32_t i = 2; i <= n; i++) {
        pair tmp{0};
        if (coordinates[i] < min.location) {
            min.ind = i;
            min.location = coordinates[i];
        }

        if (coordinates[i] > max.location) {
            max.ind = i;
            max.location = coordinates[i];
        }
        tmp.index_min = min.ind;
        tmp.index_max = max.ind;
        answer.push_back(tmp);
    }

    for (auto val : answer) {
        if (val.index_min < val.index_max)
            cout << val.index_min << " " << val.index_max << '\n';
        else
            cout << val.index_max << " " << val.index_min << '\n';
    }

    return 0;
}

