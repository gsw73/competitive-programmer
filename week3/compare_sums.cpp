//
// Created by Gregory Walter on 5/8/20.
//
// INPUT:
// Line 1:  n, (1 ≤ n ≤ 100) length of arrays
// Line 2:  floating point numbers A[1], A[2], ..., A[n], (0.001 ≤ A[i] ≤ 1000)
// Line 3:  floating point numbers B[1], B[2], ..., B[n], (0.001 ≤ B[i] ≤ 1000)
// each floating point has exactly 3 digits after the decimal point
// OUTPUT:
// one of (no spaces)
// SUM(A)=SUM(B) OR SUM(A)>SUM(B) OR SUM(A)<SUM(B)
//

#include <iostream>
#include <iomanip>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// #define MYDEBUG

static string eq = "SUM(A)=SUM(B)";
static string gt = "SUM(A)>SUM(B)";
static string lt = "SUM(A)<SUM(B)";

static double eps = 1e-8;

void showStdin(int, double*, double*);
double float_sum( int num, double ar[] );
string compare_fp( double a, double b );

int main( int argc, char *argv[] ) {
   int num;
   double *arA;
   double *arB;
   double *tmp_p;
   double ansA;
   double ansB;
   string stdout_answer;

   cin >> num;
   arA = new double [num];
   arB = new double [num];

   double *inputArrays[2]{arA, arB};

   for (auto & inputArray : inputArrays) {
       tmp_p = inputArray;
       for ( int j = 0; j < num; j++ )
           cin >> *tmp_p++;
   }

#ifdef MYDEBUG
   showStdin(num, arA, arB);
#endif

   ansA = float_sum( num, arA );
   ansB = float_sum( num, arB );

#ifdef MYDEBUG
   cout << "ansA = " << ansA << endl;
   cout << "ansB = " << ansB << endl;
#endif

   stdout_answer = compare_fp( ansA, ansB );

   cout << stdout_answer << endl;

   return 0;
}

string compare_fp( double a, double b ) {
    auto a_minus_b = a - b;
    double b_minus_eps = b - eps;
    double b_plus_eps = b + eps;

    if ( std::abs(a_minus_b) < eps )
        return eq;
    else if ( a > b_plus_eps )
        return gt;
    else if ( a < b_minus_eps )
        return lt;
    else
        return "ERROR";
}

double float_sum( int num, double ar[] ) {
    double sum = 0;

    for ( int i = 0; i < num; i++ ) {
        sum += ar[i];
    }
    return sum;
}

void showStdin( int n, double arrayA[], double arrayB[] ) {
    cout << std::fixed << std::setprecision(20);
    cout << n << endl;
    double *bothArrays[2]{ arrayA, arrayB };
    double *tmp_p;
    
    for ( int i = 0; i < 2; i++ ) {
        if (i != 0) cout << endl;
        tmp_p = bothArrays[i];
        for (int j = 0; j < n; j++) {
            if (j != 0) cout << " ";
            cout << *tmp_p++;
        }
    }
    cout << endl;
}

