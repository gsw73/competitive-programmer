//
// Created by Gregory Walter on 5/20/20.
//

#include <iostream>
#include <cinttypes>
#include <array>
#include <random>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::array;
using std::shuffle;

static const uint32_t N = 1000;

int main(int argc, char *argv[]) {
    std::ofstream myfile;
    array<uint32_t, N> x{0};
    array<uint32_t, N> y{0};

    myfile.open("../week4/examples/mandist.txt");

    // generate random numbers for x
    std::default_random_engine generator(25);
    std::uniform_int_distribution<uint32_t> distribution(0,10000);
    for ( uint32_t i = 0; i < N; i++ ) {
        uint32_t num = distribution(generator);
        x.at(i) = num;
    }

    // generate consecutive numbers for y, then shuffle
    for ( uint32_t i = 0; i < N; i++) {
        y.at(i) = i;
    }

    // shuffle y
    shuffle(y.begin(), y.end(), std::default_random_engine(25));

    myfile << N << endl;
    for ( uint32_t i = 0; i < N; i++ ) {
        myfile << x.at(i) << " " << y.at(i) << endl;
    }
    myfile.close();

    return 0;
}

