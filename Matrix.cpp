#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdbool.h>
#include <vector>
#include "Matrix.hpp"


using namespace std;

namespace zich{
    // CONSTRUCTORS

    Matrix::Matrix(const vector<double> & identity, int rows, int columns){

    };
    Matrix::Matrix(){

    };

    // ADDITION
    Matrix operator+(const Matrix & mat2, const Matrix & mat1)
    {
        return mat2;
    }
    Matrix &operator+=(Matrix & mat, double num)
    {
        return mat;
    }
    Matrix Matrix::operator++(int)
    {
        return Matrix();
    }

    // SUBTRACTION
    Matrix &operator-(Matrix & mat)
    {
        return mat;
    }
    Matrix operator-(Matrix & mat2, Matrix & mat1)
    {
        return mat1;
    }
    Matrix Matrix::operator--()
    {
        return Matrix();
    }
    Matrix operator-=(Matrix & mat, double num)
    {
        return mat;
    }

    // MULTIPLICATION

    Matrix operator*(Matrix & mat, Matrix & mult)
    {
        return mat;
    }
    Matrix operator*(Matrix & mat, double dub)
    {
        return mat;
    }
    Matrix operator*(double dub, Matrix & mat)
    {
        return mat;
    }
    Matrix operator*= (Matrix & mat, double dub)
    {
        return mat;
    }
    Matrix operator*= (double dub, Matrix& mat)
    {
        return mat;
    }
    // BIGGER THAN


    bool operator>(Matrix & mat1, Matrix & mat2)
    {
        return true;
    }
    bool operator>=(Matrix & mat1, Matrix & mat2)
    {
        return true;
    }

    // LESS THAN

    bool operator<(Matrix & mat1, Matrix & mat2)
    {
        return true;
    }
    bool operator<=(Matrix & mat1, Matrix & mat2)
    {
        return true; 
    }

    // EQUALS


    bool operator==(Matrix & mat1, Matrix & mat2)
    {
        return true;
    }
    bool operator!=(Matrix mat1, Matrix & mat2)
    {
        return true;
    }

    // INPUT OUTPUT OPERATORS 

    ostream& operator << (ostream& os, const Matrix & mat)
    {
        return os;
    }
    istream& operator >> (istream & is, Matrix& inp)
    {
        return is;
    }
}
