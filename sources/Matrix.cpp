#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdbool.h>
#include <vector>
#include "Matrix.hpp"

constexpr int zero = 48;
constexpr int nine = 57;
using namespace std;

// auxilary functions
double mult_row_by_col(const zich::Matrix & leftMat, const zich::Matrix & rightMat, int row, int column)
{
    if (leftMat.getNumCols() != rightMat.getNumRows())
    {
        throw(invalid_argument("row and column must be equal to multiply"));
    }
    if (row < 0 || column < 0)
    {
        throw (invalid_argument("row or column cant be less than 0."));
    }
    if (row >= leftMat.getNumRows())
    {
        throw(invalid_argument("row is bigger or equal to the number of rows. mult_row_by_col"));
    }
    if(column >=  leftMat.getNumCols())
    {
        throw(invalid_argument("column is bigger or equal to the number of columns."));
    }
    int i = 0;
    int j = 0;
    double sum=0;
    int cols = leftMat.getNumCols();
    for(j=0; j< cols; j++)
    {
        sum += (leftMat.getElement(row, j) * rightMat.getElement(j, column) );
    }
    return sum;
}
double sum_matrix(zich::Matrix &mat)
{
    int i=0; int j=0;
    int rows =  mat.getNumRows();
    int cols = mat.getNumCols();
    double sum= 0;
    for(i=0; i<rows; i++)
    {
        for(j=0; j< cols; j++)
        {
            sum += mat.getElement(i,j);
        }
    }
    return sum;
}

namespace zich{
    // makes a string representation of the matrix
    // returns a copy of the string
    string Matrix::toString() const
    {
        string str;
        int i=0; int j=0;
        for(i=0; i< this->_numRows; i++)
        {
            str.push_back('[');
            for(j=0;j< this->_numColumns; j++)
            {
                str.append(to_string(this ->getElement(i,j)));
                if(j == (this-> _numColumns) - 1)
                {}
                else
                {str.push_back(' ');}
            }
            str.push_back(']');
            str.push_back('\n');
        }
        return str;
    }
    // operators
    // addition
    // returns a copy of the matrix
    Matrix Matrix::operator+() const{
        return Matrix(this->_identity, this->_numRows, this-> _numColumns);
    }
    Matrix Matrix::operator+(Matrix & mat1) const
    {
        if (mat1.getNumCols() != this-> _numColumns)
        {
            throw(invalid_argument("number of columns is not equal, operator+"));
        }
        if(mat1.getNumRows() != this-> _numRows)
        {
            throw(invalid_argument("number of rows in not equal, operator+"));
        }
        vector<double> vec;
        int i=0; int j=0;
        for(i=0; i< this-> _numRows; i++)
        {
            for(j=0; j< this->_numColumns; j++)
            {
                vec.push_back(this->getElement(i, j) + mat1.getElement(i, j));
            }
        }
        return Matrix(vec, this->_numRows, this->_numColumns);
    }
    // postfix operator
    // iterates one by one and increments by num each element
    // returns the previous matrix
    Matrix Matrix::operator++( int )
    {
        if(this->_numRows == 0 || this-> _numColumns == 0)
        {
            throw(invalid_argument("matrix has row length 0 or column length 0"));
        }
        Matrix mat(*this); // before getting updated this is the return value
        size_t i = 0; size_t j = 0;
        size_t row = 0;
        size_t columns = (size_t)(this -> _numColumns);
        for(i=0; i< (this->_numRows); i++)
        {
            row = i * columns;
            for(j=0; j< (this->_numColumns); j++)
            {
                (this->_identity).at(row + j) ++;
            }
        }
        return mat;
    }
    
    // prefix operator 
    // iterates one by one and increments by num each element
    // returns the updated matrix
    Matrix & Matrix::operator++()
    {
        if(this->_numRows == 0 || this-> _numColumns == 0)
        {
            throw(invalid_argument("matrix has row length 0 or column length 0"));
        }
        size_t i = 0; size_t j = 0;
        size_t row = 0;
        size_t columns = (size_t)(this->_numColumns);
        for(i=0; i< this->_numRows; i++)
        {
            row = i * columns;
            for(j=0; j< columns; j++)
            {    // returns by reference can be added with default operator ++ for double
                (this->_identity).at(row + j) ++;
            }
        }
        return *this; // returns updated matrix
    }
    // iterates one by one and increments by num each element
    // returns the updated matrix
    Matrix & Matrix::operator+=(double num)
    {   
        if(this->_numRows == 0 || this-> _numColumns == 0)
        {
            throw(invalid_argument("matrix has row length 0 or column length 0"));
        }
        size_t i = 0; size_t j = 0;
        size_t row = 0;
        size_t columns = (size_t)(this-> _numColumns);
        for(i=0; i< this->_numRows; i++)
        {
            row = i * columns;
            for(j=0; j< columns; j++)
            {   // returns by reference can be added with default operator += for double
                (this->_identity).at(row + j) += num; 
            }
        }
        return *this;
    }
    // adds another matrix to the current matrix and returns the current matrix reference
    Matrix & Matrix::operator+=(Matrix & mat)
    {
        if(this-> _numRows != mat.getNumRows() || this-> _numColumns != mat.getNumCols())
        {throw(invalid_argument("mat addition cant be operated with different matrix sizes. operator+="));}
        size_t i;
        size_t j;
        size_t cols =  (size_t)(mat.getNumCols());
        for(i =0; i< this ->_numRows; i++)
        {
            for(j =0; j<cols; j++)
            {
                this-> _identity.at(i * cols + j) += mat.getElement(i,j);
            }
        }
        return *this;
    }

    // subtraction
    Matrix Matrix::operator-(Matrix & mat)
    {
        if (mat.getNumCols() != (this-> _numColumns) )
        {
            throw(invalid_argument("number of columns is not equal, operator-"));
        }
        if(mat.getNumRows() != (this-> _numRows) )
        {
            throw(invalid_argument("number of rows in not equal, operator-"));
        }
        vector<double> vec;
        int i=0; int j=0;
        int rows = mat.getNumRows();
        int columns = mat.getNumCols();
        for(i=0; i< rows; i++) // iterate one by one and push to a new vector the new values
        {
            for(j=0; j< columns; j++)
            {
                vec.push_back( (this -> getElement(i,j)) - mat.getElement(i,j));
            }
        }
        return Matrix(vec,rows,columns); // use constructor to returns the new matrix
    }
    Matrix Matrix::operator-()
    {
        size_t i = 0; size_t j = 0;
        size_t rows = (size_t)(this->_numRows);
        size_t cols = (size_t)(this->_numColumns);
        vector<double> vec = this->_identity;
        for(i=0; i< rows; i++)
        {
            for(j=0; j< cols; j++)
            {
                vec.at(cols * i + j)*= -1;
            }
        }
        return Matrix(vec, this->_numRows, this->_numColumns);
    }
    // postfix operator
    // iterates one by one the decreases the elements by one
    // returns a copy of the previous matrix
    Matrix Matrix::operator--( int )
    {
        if(this->_numRows == 0 || this-> _numColumns == 0)
        {
            throw(invalid_argument("matrix has row length 0 or column length 0"));
        }
        Matrix mat(*this);
        size_t i = 0; size_t j = 0;
        size_t rows =  (size_t)(this ->getNumRows());
        int columns = this -> getNumCols();
        for(i =0; i< rows; i++)
        {
            for(j=0; j< columns; j++)
            {
                (this -> _identity).at(i * rows + j) --;
            }
        }
        return mat; 
    }
    // prefix operator
    // iterates one by one the decreases the elements by one
    // returns the updated matrix
    Matrix & Matrix::operator--()
    {
        if(this->_numRows == 0 || this-> _numColumns == 0)
        {
            throw(invalid_argument("matrix has row length 0 or column length 0"));
        }
        size_t i = 0; size_t j = 0;
        size_t rows =  (size_t)(this ->getNumRows());
        int columns = this -> getNumCols();
        for(i =0; i< rows; i++)
        {
            for(j=0; j< columns; j++)
            {
                (this -> _identity).at(i * rows + j) --;
            }
        }
        return *this;
    }
    // iterates through all the elements in the matrix and subtracts each by num
    // returns a reference to the updated matrix
    Matrix & Matrix::operator-=(double num)
    {
        if(this->_numRows == 0 || this-> _numColumns == 0)
        {
            throw(invalid_argument("matrix has row length 0 or column length 0"));
        }
        size_t i = 0; size_t j = 0;
        size_t row = 0;
        size_t columns = (size_t)(this->_numColumns);
        for(i=0; i< columns; i++)
        {
            row = i * columns;
            for(j=0; j< columns; j++)
            {   // returns by reference can be added with default operator -= for double
                (this->_identity).at(row + j) -= num; 
            }
        }
        return *this;
    }

    // multiplication
    // multiplies matrixes by definition left row by right column
    Matrix Matrix::operator*(Matrix & mult)
    {
        if(this->getNumCols() != mult.getNumRows())
        {
            throw(invalid_argument("cannot multiply matrixes with different amount of rows and columns. operator*"));
        }

        vector<double> vec;
        int cols = mult.getNumCols();
        int i=0; int j=0;
        double sum = 0;
        for(i=0; i< (this -> _numRows); i++)
        {
            for(j=0; j< cols; j++)
            {
                vec.push_back(mult_row_by_col(*this, mult, i, j));
            }
        }
        return Matrix(vec, this->_numRows, mult.getNumCols());
    }
    // iterates through each element and multiplies it by dub
    // returns a copy of the result matrix
    Matrix Matrix::operator*(double dub) const
    {
        vector<double> vec;
        int i=0; int j=0;
        for(i=0; i< this->_numRows; i++)
        {
            for(j=0; j< this->_numColumns; j++)
            {
                vec.push_back((this->getElement(i,j)) * dub);
            }
        }
        return Matrix(vec, this->_numRows, this->_numColumns);
    }
    // multiplies the matrix by a double
    // returns reference to the updated matrix 
    Matrix & Matrix::operator*=(double dub)
    {
        vector<double> vec;
        int i=0; int j=0;
        for(i=0; i< this->_numRows; i++)
        {
            for(j=0; j< this->_numColumns; j++)
            {
                vec.push_back((this->getElement(i,j)) * dub);
            }
        }
        this -> _identity = vec;
        return *this;
    }
    // multiplies a double by matrix
    // returns a copy of the result matrix
    Matrix operator*(double dub, const Matrix & mat)
    {
        return (mat * dub);
    }
    Matrix & Matrix::operator*=(Matrix & mult)
    {
        *this = (*this) * (mult);
        return *this;
    }
    // comparisons
    // return true if the sum of the first matrix is bigger than the sum of the second matrix
    bool Matrix::operator>(Matrix & mat2)
    {
        return (sum_matrix(*this) > sum_matrix(mat2));
    }
    // reutnr true if the sum of the first matrix is bigger than or equal to the sum of the second matrix
    bool Matrix::operator>=(Matrix & mat2)
    {
        return (sum_matrix(*this) >= sum_matrix(mat2));
    }

    // lt
    // return true if the sum of the first matrix is less than the sum of the second matrix
    bool Matrix::operator<(Matrix & mat2)
    {
        return (sum_matrix(*this) < sum_matrix(mat2));
    }
    // return true if the sum of the first matrix is less or equal to the second matrix
    bool Matrix::operator<=( Matrix & mat2)
    {
        return (sum_matrix(*this) <= sum_matrix(mat2));
    }
    
    // eq
    // reuturns true if the sum of the matrixes is equal
    bool Matrix::operator==(Matrix & mat2)
    {
        return (sum_matrix(*this) == sum_matrix(mat2));
    }
    // returns true is the sum of the matrixes is not equal
    bool Matrix::operator!=(Matrix & mat2)
    {
        return (sum_matrix(*this) != sum_matrix(mat2));
    }

    // input output
    // outputs a string representation of mat to os
    ostream & operator<<(ostream& os, const Matrix & mat)
    {
        os << ( mat.toString() );
        return os;
    }   
    // receives string matrix representation and parses it to a matrix
    istream & operator>>(istream& is, Matrix & inp)
    {
        // format is as specified : [1 2 3, 5 6 7, 9 8 7]
        string str;
        is >> str;
        int num_rows=1;
        int num_columns = 0;
        size_t size = str.size();
        int index = 0;
        if (str.at(0) != '[' || str.at(size -1) != ']')
        {
            throw(invalid_argument("brackets are not found"));
        }
        bool double_space= false;
        // check for double space
        for(size_t i=0; i< size; i++)
        {
            if(str.at(i) == ' ')
            {
                if(double_space)
                {
                    throw(invalid_argument("invalid double space found in the input."));
                }
                double_space = true;
            }
            else{
                double_space = false;
            }
        }
        // check for invalid characters
        char c = 0;
        for(size_t i=1; i< size-1; i++)
        {
            c = str.at(i);
            if( (c < zero || c > nine) && (c != ' ') && (c != ',') && (c != '.')) // not a digit and not a proper char
            {
                throw(invalid_argument("invalid character found in the input."));
            }
        }
        // check for invalid space before the first char
        if(str.at(1) == ' ' || str.at(size-2) == ' ')
        {
            throw(invalid_argument("space found before the first char or before the last char."));
        }
        bool was_comma = false;
        // check for space after comma
        for(size_t i=0; i< size-1; i++)
        {
            if(was_comma && str.at(i) != ' ')
            {
                throw(invalid_argument("space not found after comma."));
            }
            if(str.at(i) == ',' && !was_comma)
            {
                was_comma = !(was_comma);
            }
            else
            {
                was_comma = false;
            }
        }
        // check for the same amount of numbers between each commas
        int rowlen = 0;
        int current_rowlen = 0;
        was_comma = false;
        for(size_t i=1; i< size-1; i++)
        {
            if( !was_comma && str.at(i) == ' ') // identify the length of the first row and check out that is the length of the row
            {
                rowlen +=1;
            }
            if( !was_comma && str.at(i) == ',') // if we received a comma then differ the first row from the other ones 
            {
                i++;
                was_comma = !was_comma;
            }
            else if(was_comma) // if the first comma already appeared
            {
                if(str.at(i) == ' ') // if we got a space then another number appeared, we already checked there is no double space or more
                {
                    current_rowlen +=1 ;
                }
                if(str.at(i) == ',') // if we got another comma, then check if the length of the current comma is different from the first row
                {
                    i++;
                    if(current_rowlen != rowlen) // if it's different then throw.
                    {
                        throw(invalid_argument("found a row that has different length from another other row"));
                    }
                    current_rowlen = 0; // else keep running.
                }
            }
        }
        if(rowlen != current_rowlen) // cover for the case in which the comma and space ends the row
        {
            throw(invalid_argument("found a row that has different length from another other row"));
        }
        int num_dots = 0;
        // check for dot where there is no number before it
        // check for two dots or more in the same number
        for(size_t i=1; i< size-1; i++)
        {
            if(str.at(i) == '.')
            {
                num_dots+=1;
                if( (str.at(i-1) > nine) && (str.at(i-1) < zero) )
                {
                    throw(invalid_argument("dot without a number before it."));
                }
            }
            if(str.at(i) == ' ')
            {
                num_dots = 0;
            }
            if(num_dots >= 2)
            {
                throw(invalid_argument("two dots in the same number."));
            }
        }
        string number;
        vector<double> vec;
        // construct the vector
        for(size_t i=1; i< size-1; i++)
        {
            c = str.at(i);
            if(c == ',' || c == ' ') // new number is now contructed last number inserted to the vector
            {
                if( (!number.empty()) )
                {
                    vec.push_back(stod(number));
                }
                number = "";
                i++;
            }
            while(i < size-1 && c != ' ' && c != ',') // construct a number
            { 
                c = str.at(i);
                number.push_back(c);
                i++;
            }
        }
        num_columns = (int)( vec.size() / (size_t)num_rows );
        inp = Matrix(vec, num_rows, num_columns);
        return is;
    }
}
