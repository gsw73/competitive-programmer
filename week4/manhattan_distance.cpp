//
// Created by Gregory Walter on 5/20/20.
//

// INPUT:
// Line 1:  integer n (1 ≤ n ≤ 100,000), the number of points on a line
// Line 2 to Line n+1:  coordinate x_i, y_i of the i-th point (0 ≤ x_i, y_i ≤ 10^9), an integer;
// all points are different
// OUTPUT:
// Print n lines, i-th line contains two numbers f_i and s_i (1 ≤ f_i, s_i ≤ i), the indices of
// two points with max Manhattan distance among first i points

#include <iostream>
#include <cinttypes>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

struct vertex_ext_t {
    uint32_t vertex;
    int32_t distance;
};

struct coord_t {
    uint32_t x;
    uint32_t y;
};

struct pair_t {
    uint32_t vertex_a;
    uint32_t vertex_b;
};

inline void max_distance(vertex_ext_t *saved_vertex, uint32_t current_vertex, int32_t val);

inline void min_distance(vertex_ext_t *saved_vertex, uint32_t current_vertex, int32_t val);

int main(int argc, char *argv[]) {
    uint32_t n;
    vector<coord_t> coordinates;
    vector<pair_t> answer;
    vertex_ext_t max_xpluy{0};
    vertex_ext_t min_xpluy{0};
    vertex_ext_t max_xminy{0};
    vertex_ext_t min_xminy{0};

    cin >> n;

    // don't use location 0 - coordinates are numbered from 1
    coordinates.push_back({0, 0});
    for (uint32_t i = 0; i < n; i++) {
        uint32_t x, y;
        cin >> x >> y;
        coordinates.push_back({x, y});
    }

    // seed min and max with first coordinate since the first answer is always "1 1"
    max_xpluy.vertex = 1;
    max_xpluy.distance = coordinates[1].x + coordinates[1].y;
    min_xpluy.vertex = 1;
    min_xpluy.distance = coordinates[1].x + coordinates[1].y;
    max_xminy.vertex = 1;
    max_xminy.distance = coordinates[1].x - coordinates[1].y;
    min_xminy.vertex = 1;
    min_xminy.distance = coordinates[1].x - coordinates[1].y;

    // first answer is always the same since single coordinate
    answer.push_back({1, 1});

    for (uint32_t i = 2; i <= n; i++) {
        int32_t sum, dif;

        // for each input vertex, calculate sum and dif per formula
        sum = coordinates[i].x + coordinates[i].y;
        dif = coordinates[i].x - coordinates[i].y;

        // always save running max and min of each sum and dif
        max_distance(&max_xpluy, i, sum);
        min_distance(&min_xpluy, i, sum);
        max_distance(&max_xminy, i, dif);
        min_distance(&min_xminy, i, dif);

        // calculate max manhattan distance for current list of vertices
        int32_t manhattan_a, manhattan_b;
        pair_t vertices{0};

        manhattan_a = max_xpluy.distance - min_xpluy.distance;
        manhattan_b = max_xminy.distance - min_xminy.distance;

        if (manhattan_a > manhattan_b) {
            vertices = {max_xpluy.vertex, min_xpluy.vertex};
        } else {
            vertices = {max_xminy.vertex, min_xminy.vertex};
        }

        answer.push_back(vertices);
    }

    for (auto &val : answer) { cout << val.vertex_a << " " << val.vertex_b << '\n'; }
    cout << endl;

    return 0;
}

void max_distance(vertex_ext_t *saved_vertex, uint32_t current_vertex, int32_t val) {
    if (val >= saved_vertex->distance) {
        saved_vertex->vertex = current_vertex;
        saved_vertex->distance = val;
    }
}

void min_distance(vertex_ext_t *saved_vertex, uint32_t current_vertex, int32_t val) {
    if (val < saved_vertex->distance) {
        saved_vertex->vertex = current_vertex;
        saved_vertex->distance = val;
    }
}
