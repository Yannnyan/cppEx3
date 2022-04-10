#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stdbool.h>
#include <vector>

using namespace std;

// auxilary functions
double mult_row_by_col(zich::Matrix & leftMat, zich::Matrix & rightMat, int row, int column) const;
double sum_matrix() const;

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
            Matrix(const vector<double> & identity, int row, int column);
            Matrix(const Matrix &mat);
            Matrix();
            // Destructors
            // ~
            // operators
            // addition
            Matrix operator+(const Matrix & mat1);
            // postfix operator
            Matrix operator++( int );
            // prefix operator 
            Matrix & operator++();
            Matrix & operator+=(double num);


            // subtraction
            Matrix operator-(const Matrix & mat);
            // unary - prefix operator
            Matrix operator-();
            // postfix operator
            Matrix operator--( int );
            // prefix operator
            Matrix & operator--();
            Matrix & operator-=(double num);

            // multiplication
            Matrix operator*(const Matrix & mult);
            Matrix operator*(double dub);
            friend Matrix operator*(double dub, const Matrix & mat);

            Matrix & operator*= (double dub);
            
            // comparisons
            
            // bigger than
            bool operator>(const Matrix & mat2);
            bool operator>=(const Matrix & mat2);

            // lt
            bool operator<(const Matrix & mat2);
            bool operator<=(const Matrix & mat2);
            
            // eq
            bool operator==(const Matrix & mat2);
            bool operator!=(const Matrix & mat2);

            // input output
            friend ostream & operator<<(ostream& os, const Matrix & mat);
            friend istream & operator>>(istream& is, Matrix & inp);
    };
}