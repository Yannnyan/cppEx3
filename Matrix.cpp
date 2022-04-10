#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdbool.h>
#include <vector>
#include "Matrix.hpp"

#define DEFAULT_ROWS 10
#define DEFAULT_COLS 10
using namespace std;

// auxilary functions
double mult_row_by_col(const zich::Matrix & leftMat, const zich::Matrix & rightMat, int row, int column) const
{
    if (leftMat.getNumCols() != rightMat.getNumRows())
    {
        throw(invalid_arguemnt("row and column must be equal to multiply"));
    }
    if (row < 0 || column < 0)
    {
        throw (invalid_argument("row or column cant be less than 0."));
    }
    if (row >= leftMat.getNumRows())
    {
        throw(invalid_argument("row is bigger or equal to the number of rows."));
    }
    else if(column >=  leftMat.getNumCols())
    {
        throw(invalid_argument("column is bigger or equal to the number of columns."));
    }
    int i,j;
    double sum=0;
    int rows = leftMat.getNumRows();
    int cols = leftMat.getNumCols();
    for(j=0; j< cols; j++)
    {
        sum += (leftMat.getElement(row, j) * rightMat.getElement(j, column) );
    }
    return sum;
}
double sum_matrix(zich:: Matrix mat) const
{
    int i,j;
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
   // constructors
    inline Matrix::Matrix(const vector<double> & identity, int row, int column)
    {
        int size = identity.size();
        if (size > row * column) // cant initialize the matrix because some elements will not be inserted
        {
            throw(invalid_argument("size of identity bigger than the matrix specified"));
        }
        else if (size < row * column) // cant initialize the matrix because some cells will be missing
        {
            throw(invalid_argument("size of identity smaller than the matrix specified"));
        }
        this -> _numRows = row;
        this -> _numColumns = column;
        this -> _identity = identity;
    }
    inline Matrix::Matrix(const Matrix& mat)
    {
        this ->_numRows = mat.getNumRows();
        this -> _numColumns = mat.getNumCols();
        this -> _identity = mat.getCopyIdentity(); // using copy constructor of vector<double>
    }
    inline Matrix::Matrix() 
    {
        // creates a default matrix with 10 x 10 size, with zeros 
        this -> _numRows = DEFAULT_ROWS;
        this -> _numColumns = DEFAULT_COLS;
        vector<double> identity = vector<double>();
        for (int i=0; i< 100; i++)
        {
            identity.push_back(0);
        }
        this -> _identity = identity;
    }
    // getts and setters
     inline double Matrix::getElement(int row, int column) const
    {
         if (row < 0 || column < 0)
            {
                throw (invalid_argument("row or column cant be less than 0."));
            }
            if (row >= this ->_numRows)
            {
                throw(invalid_argument("row is bigger or equal to the number of rows."));
            }
            else if(column >= this -> _numColumns)
            {
                throw(invalid_argument("column is bigger or equal to the number of columns."));
            }
        size_t index = (size_t)( row * (this -> _numColumns) + column);
        return (this->_identity).at(index);
    }
    inline vector<double> Matrix::getCopyIdentity() const
    {
        // using copy constructor of vector<double> to generate copy of the identity vector inside the matrix private fields
        return this -> _identity;
    }
    // makes a string representation of the matrix
    // returns a copy of the string
    string Matrix::toString()
    {
        string str = "";
        int i,j;
        for(i=0; i< this->_numRows; i++)
        {
            str.push_back('[');
            for(j=0;j< this->_numColumns; j++)
            {
                str.append(to_string(this ->getElement(i,j)));
                str.push_back(' ');
            }
            str.push_back(']');
            str.push_back('\n');
        }
        return str;
    }
    // operators
    // addition
    Matrix Matrix::operator+(const Matrix & mat1)
    {
        if (mat1.getNumCols() != this-> _numColumns)
        {
            throw(invalid_argument("number of columns is not equal, operator+"));
        }
        else if(mat1.getNumRows() != this-> _numRows)
        {
            throw(invalid_argument("number of rows in not equal, operator+"));
        }
        vector<double> vec;
        int i,j;
        for(i=0; i< this-> _numRows; i++)
        {
            for(j=0; j< this->_numColumns; j++)
            {
                vec.push_back(this->getElement(i, j) + mat1.getElement(i, j));
            }
        }
        this -> _identity = vec;
    }
    // postfix operator
    // iterates one by one and increments by num each element
    // returns the previous matrix
    Matrix Matrix::operator++( int )
    {
        Matrix mat(*this); // before getting updated this is the return value
        size_t i,j;
        size_t row;
        for(i=0; i< this->_numRows; i++)
        {
            row = i * this->_numColumns;
            for(j=0; j< this->_numColumns; j++)
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
        size_t i,j;
        size_t row;
        for(i=0; i< this->_numRows; i++)
        {
            row = i * this->_numColumns;
            for(j=0; j< this->_numColumns; j++)
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
        size_t i,j;
        size_t row;
        for(i=0; i< this->_numRows; i++)
        {
            row = i * this->_numColumns;
            for(j=0; j< this->_numColumns; j++)
            {   // returns by reference can be added with default operator += for double
                (this->_identity).at(row + j) += num; 
            }
        }
        return *this;
    }


    // subtraction
    Matrix Matrix::operator-(const Matrix & mat)
    {
        if (mat.getNumCols() != this-> _numColumns)
        {
            throw(invalid_argument("number of columns is not equal, operator-"));
        }
        else if(mat.getNumRows() != this-> _numRows)
        {
            throw(invalid_argument("number of rows in not equal, operator-"));
        }
        vector<double> vec;
        int i,j;
        int rows = mat.getNumRows();
        int columns = mat.getNumCols();
        for(i=0; i< rows; i++) // iterate one by one and push to a new vector the new values
        {
            for(j=0; j< columns; i++)
            {
                vec.push_back(this -> getElement(i,j) - mat.getElement(i,j));
            }
        }
        return Matrix(vec,rows,columns); // use constructor to returns the new matrix
    }
    // postfix operator
    // iterates one by one the decreases the elements by one
    // returns a copy of the previous matrix
    Matrix Matrix::operator--( int )
    {
        Matrix mat(*this);
        size_t i, j;
        int rows =  this ->getNumRows();
        int columns = this -> getNumCols();
        for(i =0; i< rows; i++)
        {
            for(j=0; j< columns; j++)
            {
                (this -> _identity).at(i * rows + column) --;
            }
        }
        return mat; 
    }
    // prefix operator
    // iterates one by one the decreases the elements by one
    // returns the updated matrix
    Matrix & Matrix::operator--()
    {
        size_t i, j;
        int rows =  this ->getNumRows();
        int columns = this -> getNumCols();
        for(i =0; i< rows; i++)
        {
            for(j=0; j< columns; j++)
            {
                (this -> _identity).at(i * rows + column) --;
            }
        }
        return *this;
    }
    // iterates through all the elements in the matrix and subtracts each by num
    // returns a reference to the updated matrix
    Matrix & Matrix::operator-=(double num)
    {
        size_t i,j;
        size_t row;
        for(i=0; i< this->_numRows; i++)
        {
            row = i * this->_numColumns;
            for(j=0; j< this->_numColumns; j++)
            {   // returns by reference can be added with default operator -= for double
                (this->_identity).at(row + j) -= num; 
            }
        }
        return *this;
    }

    // multiplication
    // multiplies matrixes by definition left row by right column
    Matrix Matrix::operator*(const Matrix & mult)
    {
        vector<double> vec;
        int i,j;
        double sum;
        for(i=0; i< (this -> _numRows); i++)
        {
            for(j=0; j< (this -> _numColumns); j++)
            {
                vec.push_back(this ->mult_row_by_col(*this, mult, i, j));
            }
        }
        return Matrix(vec, (this -> _numRows), (this -> _numColumns));
    }
    // iterates through each element and multiplies it by dub
    // returns a copy of the result matrix
    Matrix Matrix::operator*(const double dub)
    {
        vector<double> vec;
        int i, j;
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
        int i, j;
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
    Matrix operator*(const double dub, const Matrix & mat)
    {
        return (mat * dub);
    }

    // comparisons
    // return true if the sum of the first matrix is bigger than the sum of the second matrix
    bool Matrix::operator>(const Matrix & mat2)
    {
        return (sum_matrix(*this) > sum_matrix(mat2));
    }
    // reutnr true if the sum of the first matrix is bigger than or equal to the sum of the second matrix
    bool Matrix::operator>=(const Matrix & mat2)
    {
        return (sum_matrix(*this) >= sum_matrix(mat2));
    }

    // lt
    // return true if the sum of the first matrix is less than the sum of the second matrix
    bool Matrix::operator<(const Matrix & mat2)
    {
        return (sum_matrix(*this) < sum_matrix(mat2));
    }
    // return true if the sum of the first matrix is less or equal to the second matrix
    bool Matrix::operator<=(const Matrix & mat2)
    {
        return (sum_matrix(*this) <= sum_matrix(mat2));
    }
    
    // eq
    // reuturns true if the sum of the matrixes is equal
    bool Matrix::operator==(const Matrix & mat2)
    {
        return (sum_matrix(*this) == sum_matrix(mat2));
    }
    // returns true is the sum of the matrixes is not equal
    bool Matrix::operator!=(const Matrix & mat2)
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
        int num_columns;
        int size = str.size();
        int index = 0;
        if (str.at(0) != '[' || str.at(size -1) != ']')
        {
            throw(invalid_argument("brackets are not found"));
        }
        bool double_space= false;
        // check for double space
        for(int i=0; i< size; i++)
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
        char c;
        for(int i=1; i< size-1; i++)
        {
            c = str.at(i);
            if( (c < 48 || c > 57) && (c != ' ') && (c != ',') && (c != '.'))
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
        for(int i=0; i< size-1; i++)
        {
            if(was_comma && str.at(i) != ' ')
            {
                throw(invalid_argument("space not found after comma."));
            }
            if(str.at(i) == ',')
            {
                was_comma = true;
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
        for(int i=1; i< size-1; i++)
        {
            if(was_comma == false && str.at(i) == ' ') // identify the length of the first row and check out that is the length of the row
            {
                rowlen +=1;
            }
            if(was_comma == false && str.at(i) == ',') // if we received a comma then differ the first row from the other ones 
            {
                i++;
                was_comma = true;
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

        // check for dot in wrong places or double dot
        for(int i=1; i< size-1; i++)
        {
            if()
        }

        string number = "";
        vector<double> vec;
        char c;
        // construct the vector
        for(int i=1; i< size-1; i++)
        {
            c = str.at(i);
            if(c == ',' || c == ' ') // new number is now contructed last number inserted to the vector
            {
                if(!number.empty())
                    vec.push_back(stod(number));
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
    }
}
