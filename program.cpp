#include <iostream>
#include <string>
#include "Matrix.hpp"

using namespace std;
using namespace zich;


// [1 1 1 1], [1 1 1 1], [1 1 1 1]\n ->
// [1 1 1 1]
//  [1 1 1 1]
//  [1 1 1 1]\n ->
// [1
// 1
// 1
// 1]

int main()
{
    Matrix mat;
    istringstream is5{"[1 1 1 1], [1 1 1 1], [1 1 1 1]\n"};
    istringstream is6{",[1 2 3 4], [1 1 1 1], [1 2 2 2]\n"};
    istringstream is7{"[1 2 3 4], [1 1 1 1], [1, 2 2 2]\n"};
    istringstream is8{"[1 2 1.1.1 3 4], [1 1 1 1], [1 2 2 2]\n"};
    is5 >> mat;
    cout << mat;
    is6 >> mat;
    cout << mat;
    is8 >> mat;
    cout << mat;
}













