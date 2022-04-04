#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;


namespace zich{
    class Matrix{
        private:

        public:
            Matrix(vector<double> identity, int row, int column);

            // operators
            
            // addition
            Matrix operator+(Matrix & mat2);
            Matrix & operator++();
            Matrix operator+=(double num);


            // subtraction
            Matrix operator-(Matrix & mat2);
            Matrix operator--();
            Matrix operator-=(double num);

            // multiplication
            Matrix operator*(Matrix & mult);
            Matrix operator*(double dub);
            
            // comparisons
            
            // bigger than
            bool operator>(Matrix & mat2);
            bool operator>=(Matrix & mat2);

            // lt
            bool operator<(Matrix & mat2);
            bool operator<=(Matrix & mat2);
            
            // eq
            bool operator==(Matrix & mat2);
            bool operator!=(Matrix & mat2);

            // input output
            void operator<<(Matrix & mat);
            void operator>>(Matrix & toInput);
    }


}