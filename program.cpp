
#include <iostream>
#include <string>
#include "Matrix.hpp"

using namespace std;





int main()
{
    istringstream is7{"[1 1 1 1], [1 1 1 1], [1 1 1 1]\n"};
    //zich::Matrix mat;
    //is7 >> mat;
    string str;


    str = is7.str();
    
    
    cout << str;
}