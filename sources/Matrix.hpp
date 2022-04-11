#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdbool.h>
#include <vector>

using namespace std;
#define DEFAULT_ROWS 10
#define DEFAULT_COLS 10


namespace zich{
    class Matrix{
        private:
            int _numRows;
            int _numColumns;
            vector<double> _identity;
            

        public:
            // getters and setters
            int getNumRows() const {return this -> _numRows;}
            int getNumCols() const {return this -> _numColumns;}
            double getElement(int row, int column) const;
            vector<double> getCopyIdentity() const;
            string toString() const;
            // Constructors
            inline Matrix(const vector<double> & identity, int row, int column);
            inline Matrix(const Matrix &mat);
            inline Matrix();
            // Destructors
            // ~
            // operators
            // addition
            Matrix operator+() const;
            Matrix operator+(Matrix & mat1) const;
            // postfix operator
            Matrix operator++( int );
            // prefix operator 
            Matrix & operator++();
            Matrix & operator+=(double num);


            // subtraction
            Matrix operator-(Matrix & mat);
            // unary - prefix operator
            Matrix operator-();
            // postfix operator
            Matrix operator--( int );
            // prefix operator
            Matrix & operator--();
            Matrix & operator-=(double num);

            // multiplication
            Matrix operator*(Matrix & mult);
            Matrix operator*(double dub) const;
            friend Matrix operator*(double dub, const Matrix & mat);

            Matrix & operator*= (double dub);
            
            // comparisons
            
            // bigger than
            bool operator>(Matrix & mat2);
            bool operator>=( Matrix & mat2);

            // lt
            bool operator<(Matrix & mat2);
            bool operator<=( Matrix & mat2);
            
            // eq
            bool operator==( Matrix & mat2);
            bool operator!=( Matrix & mat2);

            // input output
            friend ostream & operator<<(ostream& os, const Matrix & mat);
            friend istream & operator>>(istream& is, Matrix & inp);
    };
}
// constructors
    inline zich::Matrix::Matrix(const vector<double> & identity, int row, int column)
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
    inline zich::Matrix::Matrix(const Matrix& mat)
    {
        this ->_numRows = mat.getNumRows();
        this -> _numColumns = mat.getNumCols();
        this -> _identity = mat.getCopyIdentity(); // using copy constructor of vector<double>
    }
    inline zich::Matrix::Matrix() 
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
    // returns the element in row "row" and column "column".
     inline double zich::Matrix::getElement(int row, int column) const
    {
         if (row < 0 || column < 0)
            {
                throw (invalid_argument("row or column cant be less than 0. getElement"));
            }
            if (row >= (this ->_numRows) )
            {
                throw(invalid_argument("row is bigger or equal to the number of rows. getElement"));
            }
            else if(column >= (this -> _numColumns) )
            {
                throw(invalid_argument("column is bigger or equal to the number of columns. getElement"));
            }
        size_t index = (size_t)( row * (this -> _numColumns) + column);
        return (this->_identity).at(index);
    }
    // returns a copy of the matrix's identity vector
    inline vector<double> zich::Matrix::getCopyIdentity() const
    {
        // using copy constructor of vector<double> to generate copy of the identity vector inside the matrix private fields
        return this -> _identity;
    }
// auxilary functions
double mult_row_by_col(const zich::Matrix & leftMat,const zich::Matrix & rightMat, int row, int column);
double sum_matrix(zich::Matrix & mat);

