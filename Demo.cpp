/**
 * Demo file for the exercise on numbers with units
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 * 
 * Edited by Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "Matrix.hpp"
using namespace ariel;

int main() {
  
  double identity[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  double arr[3][3] = {{3, 0, 0}, {0, 3, 0}, {0, 0, 3}};
  Matrix a{identity};  // constructor taking a 2d array
  cout << a << endl;
  /* prints [1 0 0]
            [0 1 0]
            [0 0 1]*/

  cout << (-a) << endl;
  /* prints [-1 0 0]
            [0 -1 0]
            [0 0 -1]*/
  cout << (3*a) << endl;
  /* prints [-3 0 0]
            [0 -3 0]
            [0 0 -3]*/

  Matrix b{arr};
  cout << (a+b) << endl;  // prints the 0 matrix
  cout << (b-a) << endl;
  /* prints [6 0 0]
            [0 6 0]
            [0 0 6]*/

  cout << boolalpha; // print booleans as strings from now on:
  cout << (a>b) << endl;  // Prints "true"
  cout << (a<=b) << endl;  // Prints "false"
  cout << (a==Matrix{2000, "m"}) << endl;  // Prints "true"

  istringstream sample_input{"700 [ kg ]"};
  sample_input >> a;
  cout << a << endl;   // Prints "700[kg]"
  cout << (a += Matrix{1, "ton"}) << endl;  // prints "1700[kg]"
  cout << a << endl;   // Prints "1700[kg]". Note that a has changed.

  try {
    cout << (a+b) << endl;  
  } catch (const std::exception& ex) {
    cout << ex.what() << endl; // Prints "Units do not match - [m] cannot be converted to [kg]"
  }
  cout << "End of demo!" << endl;
  return 0;
}
