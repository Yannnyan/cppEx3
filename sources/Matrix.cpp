#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdbool.h>
#include <vector>
#include <stack>
#include "Matrix.hpp"
#include <math.h>

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
    if(column >=  rightMat.getNumCols())
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
double sum_matrix(const zich::Matrix &mat)
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
                if (floor(this->getElement(i,j) == this->getElement(i,j)))
                {
                    str.append(to_string((int)this->getElement(i,j)));
                }
                else
                {
                    str.append(to_string(this ->getElement(i,j)));
                }
                if(j != (this-> _numColumns) - 1)
                {str.push_back(' ');}
            }
            str.push_back(']');
            if(i != this->_numRows - 1)
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
        size_t columns = (size_t)(this -> getNumCols());
        for(i =0; i< rows; i++)
        {
            for(j=0; j< columns; j++)
            {
                (this -> _identity).at(i * columns + j) --;
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
        size_t columns = (size_t)(this -> getNumCols());
        for(i =0; i< rows; i++)
        {
            for(j=0; j< columns; j++)
            {
                (this -> _identity).at(i * columns + j) --;
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
    Matrix & Matrix::operator-=(Matrix & mat)
    {
        *this = (*this) - mat;
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
    bool Matrix::operator>(const Matrix & mat2)
    {
        if(this->_numRows < mat2.getNumRows() || this-> _numColumns < mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator>"));
        }
        if (this -> _numRows > mat2.getNumRows() || this -> _numColumns > mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator>"));
        }
        return (sum_matrix(*this) > sum_matrix(mat2));
    }
    // reutnr true if the sum of the first matrix is bigger than or equal to the sum of the second matrix
    bool Matrix::operator>=(const Matrix & mat2)
    {
        if(this->_numRows < mat2.getNumRows() || this-> _numColumns < mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator>="));
        }
        if (this -> _numRows > mat2.getNumRows() || this -> _numColumns > mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator>="));
        }
        return (sum_matrix(*this) >= sum_matrix(mat2));
    }

    // lt
    // return true if the sum of the first matrix is less than the sum of the second matrix
    bool Matrix::operator<(const Matrix & mat2)
    {
        if(this->_numRows < mat2.getNumRows() || this-> _numColumns < mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator<"));
        }
        if (this -> _numRows > mat2.getNumRows() || this -> _numColumns > mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator<"));
        }
        return (sum_matrix(*this) < sum_matrix(mat2));
    }
    // return true if the sum of the first matrix is less or equal to the second matrix
    bool Matrix::operator<=(const Matrix & mat2)
    {
        if(this->_numRows < mat2.getNumRows() || this-> _numColumns < mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator<="));
        }
        if (this -> _numRows > mat2.getNumRows() || this -> _numColumns > mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator<="));
        }
        return (sum_matrix(*this) <= sum_matrix(mat2));
    }
    
    // eq
    // reuturns true if the sum of the matrixes is equal
    bool operator==(const Matrix & mat1, const Matrix & mat2)
    {
        if(mat1._numRows < mat2.getNumRows() || mat1._numColumns < mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator=="));
        }
        if (mat1._numRows > mat2.getNumRows() || mat1._numColumns > mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator=="));
        }
        int i = 0;
        int j = 0;
        int rows = mat1.getNumRows();
        int cols = mat1.getNumCols();
        for(i =0; i< rows; i++)
        {
            for(j =0; j< cols; j++)
            {
                if(mat1.getElement(i,j) != mat2.getElement(i,j))
                {
                    return false;
                }
            }
        }
        return true;
    }
    // returns true is the sum of the matrixes is not equal
    bool operator!=(const Matrix & mat1, const Matrix & mat2)
    {
        if(mat1._numRows < mat2.getNumRows() || mat2._numColumns < mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator!="));
        }
        if (mat1._numRows > mat2.getNumRows() || mat1._numColumns > mat2.getNumCols())
        {
            throw(invalid_argument("rows and collumns must be at the same size. operator!="));
        }
        return !(mat1 == mat2);
    }

    // input output
    // outputs a string representation of mat to os
    ostream & operator<<(ostream& os, const Matrix & mat)
    {
        os << ( mat.toString() );
        return os;
    }   
    // receives string matrix representation and parses it to a matrix
    istringstream & operator>>(istringstream& is, Matrix & inp)
    {
        stack<char> s;
        vector<double> vec;
        string str;
        str = is.str();
        cout << str << endl;
        size_t size = str.size();
        // check for invalid characters
        char c = 0;
        for(size_t i=0; i< size-1; i++)
        {
            c = str.at(i);
            if((c < zero || c > nine) && c != ' ' && c != ',' && c != '.' && c != '[' && c != ']')
            {
                throw(invalid_argument("character is not valid"));
            }
        }
        // check for double valid characters
        for(size_t i=1; i< size-1; i++)
        {
            c = str.at(i);
            // check that there is no double space
            if(c == ' ' && str.at(i-1) == ' ')
            {
                throw(invalid_argument("double space detected."));
            }
            // check that there is no double ,
            if(c == ',' && str.at(i-1) == ',')
            {
                throw(invalid_argument("double , detected."));
            }
            // check that there is no double .
            if(c == '.' && str.at(i-1) == '.')
            {
                throw(invalid_argument("double . detected."));
            }
            // check that there is no double [
            if(c == '[' && str.at(i-1) == '[')
            {
                throw(invalid_argument("double [ detected."));
            }
            if(c == ']' && str.at(i-1) == ']')
            {
                throw(invalid_argument("double ] detected."));
            }
        }
        // check that the string is not starting and not ending with comma or dot or space
        if(str.at(0) == '.' || str.at(0) == ',' || str.at(0) == ' ')
        {
            throw(invalid_argument("string starts with non valid character."));
        }
        // check that there is ending for every bracket
        int bracket = 0;
        int dot = 0;
        for(size_t i=0; i< size ; i++)
        {
            c = str.at(i);
            if(c == '[')
            {
                bracket++;
            }
            if (bracket > 0) // check if a comma comes before an ending of a bracket
            {
                if(c == ',')
                {
                    throw(invalid_argument("found comma before ending a bracket."));
                }
            }
            if(c == '.')
            {
                if (dot > 0)
                {
                    throw(invalid_argument("found a dot after another dot without seperation."));
                }
                if(i >= 1)
                {
                    if (str.at(i-1) < zero && str.at(i-1) > nine)
                    {
                        throw(invalid_argument("found a dot that comes after non digit char."));
                    }
                }
                else // i == 0
                {
                    throw(invalid_argument("found dot before anything"));
                }
                dot+=1;
            }
            if(c == ' ')
            {
                dot = 0;
            }
            if (c == ']')
            {
                bracket --;
                dot = 0;
                // check that after a closing bracket comes comma
                if (str.at(i+1) != ',' && i != size-2)
                {
                    throw(invalid_argument("not found comma after closing bracket."));
                }
                if (str.at(i+1) == ',' && i != size-2)
                {
                    if(str.at(i+2) != ' ')
                    {
                        throw(invalid_argument("not found space after comma"));
                    }
                }

                
            }
            if (bracket < 0)
            {
                throw(invalid_argument("found double ending for a bracket or ending for non existing opening bracket."));
            }
        }
        if (bracket != 0)
        {
            throw(invalid_argument("found bracket with no ending."));
        }
        // iterate through the string and seperate numbers by the next format:
        // [number ], [ number], [number], [x number y]
        // traverse all the string, if found a start of a number -> enter a loop untill encounter ']' or ' ', if any other encounter throw exception
        string number;
        for(size_t i=0; i< size; i++)
        {
            c = str.at(i);
            while(((c > zero && c < nine) || c == '.') && i < size)
            {
                number.push_back(c);
                c = str.at(++i);
            }
            if(number.size() > 0)
                vec.push_back(stod(number));
            number.clear();
        }
        int num_rows = size_by_comma(str);
        inp = Matrix(vec, num_rows, (int)(vec.size() / (size_t)num_rows));
        return is;
    }
}
// gives the size of the matrix by counting the number of commas
int size_by_comma(string str)
{
    int ret = 0;
    int size = str.size();
    for(size_t i=0; i< size; i++)
    {
        if (str.at(i) == ',')
        {
            ret+=1;
        }
    }
    return ret+1;
}
// gives the size of the word by counting the number of spaces inside a row
int size_by_space(string str)
{
    int ret = 0;
    size_t size = (size_t)str.size();
    for(size_t i=0; i< size; i++)
    {
        if (str.at(i) == ' ')
        {
            ret+=1;
        }
    }
    return ret+1;
}
// splits the rows by commas
string * split_by_comma(string str)
{
    size_t size = (size_t)size_by_comma(str);
    string * ret = new string[size];
    string deli = ",";
    size_t pos = 0;
    size_t last_pos = 0;
    int at = 0;
    while ((pos = str.find(deli)) != string::npos)
    {
        string token = str.substr(last_pos, pos);
        ret[at++] = token;
        last_pos = pos;
    }
    return ret;
}
// splits the numbers inside the row to number array
string * split_by_space(string str)
{
    size_t size = (size_t)size_by_comma(str);
    string * ret = new string[size];
    string deli = " ";
    size_t pos = 0;
    size_t last_pos = 0;
    int at = 0;
    while ((pos = str.find(deli)) != string::npos)
    {
        string token = str.substr(last_pos, pos);
        ret[at++] = token;
        last_pos = pos;
    }
    return ret;
}
