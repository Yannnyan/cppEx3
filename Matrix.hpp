#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdbool.h>
#include <vector>

using namespace std;


namespace zich{
    class Matrix{
        private:

        public:
            Matrix(const vector<double> & identity, int row, int column);
            Matrix();
            // operators
            
            // addition
            friend Matrix operator+(const Matrix & mat2, const Matrix & mat1);
            Matrix operator++( int );
            friend Matrix & operator+=(Matrix & mat, double num);


            // subtraction
            friend Matrix& operator-(Matrix & mat);
            friend Matrix operator-(Matrix & mat2, Matrix & mat1);
            Matrix operator--();
            friend Matrix operator-=(Matrix & mat, double num);

            // multiplication
            friend Matrix operator*(Matrix & mat, Matrix & mult);
            friend Matrix operator*(Matrix & mat, double dub);
            friend Matrix operator*(double dub, Matrix & mat);

            friend Matrix operator*= (Matrix & mat, double dub);
            friend Matrix operator*= (double dub, Matrix& mat);
            
            // comparisons
            
            // bigger than
            friend bool operator>(Matrix & mat1, Matrix & mat2);
            friend bool operator>=(Matrix & mat1, Matrix & mat2);

            // lt
            friend bool operator<(Matrix & mat1, Matrix & mat2);
            friend bool operator<=(Matrix & mat1, Matrix & mat2);
            
            // eq
            friend bool operator==(Matrix & mat1, Matrix & mat2);
            friend bool operator!=(Matrix mat1, Matrix & mat2);

            // input output
            friend ostream & operator<<(ostream& os, const Matrix & mat);
            friend istream & operator>>(istream& is, Matrix & inp);
    };
}