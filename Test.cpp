#include "doctest.h"
#include "Matrix.hpp"
#include <vector>
#include <iostream>

using namespace std;
using namespace zich;
/**
 *  1) operations:
 *   addition, join matrix, unary plus;   subtraction, matrix cut, unary subraction;
 *   bigger than, bigger equal, less than, less than equal, equal, not equal.
 *   ++ , -- : increments or decreases by one all matrix elements
 *   scalar multiplication, matrix multiplication.
 *   input, output operators
 * 
 */


 // defining identity vectors
    vector<double> vec0 = {};
    vector<double> vec11 = {1};
    vector<double> vec22 = {1, 2, 3, 4};
    vector<double> vec23 = {1, 2, 3, 4, 5, 6};
    vector<double> vec32 = {1, 3, 5, 2, 4, 6};
    vector<double> vec33 = {1, 2, 3, 4, 5, 6};

    // defining matrix
    Matrix mat0(vec0, 0, 0);
    Matrix mat11(vec11, 1, 1);
    Matrix mat22(vec22, 2, 2);
    Matrix mat23(vec23, 2, 3);
    Matrix mat32(vec32, 3, 2);
    Matrix mat33(vec33, 3, 3);





TEST_CASE("Good input - matrix addition")
{
    vector<double> iden1{4,4,4,4};
}


TEST_CASE("Good input")
{
    
     // big vectors
    size_t bigNum1 = 250000;
    size_t bigNum2 = (size_t)(bigNum1 * 4);
    size_t bigNum3 = (size_t) (bigNum1 * 100);
    vector<double> bigVec1(bigNum1);
    vector<double> bigVec2(bigNum2);
    vector<double> bigVec3(bigNum3);
    for(size_t i=0; i< bigNum1; i++){
        bigVec1[i] = 1;
    }
    for(size_t i=0; i< bigNum2; i++){
        bigVec2[i] = 2;
    }
    for(size_t i=0; i< bigNum3; i++){
        bigVec3[i] = 3;
    }
    Matrix bigMat1(bigVec1, 500, 500);
    Matrix bigMat2(bigVec2, 1000, 1000);
    Matrix bigMat3(bigVec3, 5000, 5000);
    // check plus operator
   CHECK_NOTHROW(mat0 + mat0);

    // check unary plus
   CHECK_NOTHROW(mat11++);

   // check scalar multiplication
   CHECK_NOTHROW(3 * bigMat3);

   // check matrix multiplication, must be that the left matrix column equal to the right matrix row
   CHECK_NOTHROW(bigMat1 * bigMat1);

   CHECK_NOTHROW(mat23 * mat32);
   // check matrix output operator

   CHECK_NOTHROW(cout << mat33);
   //check matrix input operator

   Matrix mat(vec0, 0, 0);
   //CHECK_NOTHROW(mat22 >> mat);

}

    /**
 * 1) matrix addition or subtraction must be between matrix with equal row length and column length
 * 2) 
 * 
 * 
 */

TEST_CASE("Bad Input- addition between matrixes"){
    
     // big vectors
    size_t bigNum1 = 250000;
    size_t bigNum2 = (size_t)(bigNum1 * 4);
    size_t bigNum3 = (size_t) (bigNum1 * 100);
    vector<double> bigVec1(bigNum1);
    vector<double> bigVec2(bigNum2);
    vector<double> bigVec3(bigNum3);
    for(size_t i=0; i< bigNum1; i++){
        bigVec1[i] = 1;
    }
    for(size_t i=0; i< bigNum2; i++){
        bigVec2[i] = 2;
    }
    for(size_t i=0; i< bigNum3; i++){
        bigVec3[i] = 3;
    }
    Matrix bigMat1(bigVec1, 500, 500);
    Matrix bigMat2(bigVec2, 1000, 1000);
    Matrix bigMat3(bigVec3, 5000, 5000);
    /* check throws plus operator */
    /* RULE 1 */
    // checking mat 0
    CHECK_THROWS(mat11 + mat0);
    CHECK_THROWS(mat22 + mat0);
    CHECK_THROWS(mat33 + mat0);
    CHECK_THROWS(mat23 + mat0);
    CHECK_THROWS(mat32 + mat0);

    // check other side
    CHECK_THROWS(mat0 + mat11);
    CHECK_THROWS(mat0 + mat22);
    CHECK_THROWS(mat0 + mat33);
    CHECK_THROWS(mat0 + mat23);
    CHECK_THROWS(mat0 + mat32);
    
    /* check normal matrixes */
    /* RULE 1 */
    CHECK_THROWS(mat11 + mat22);
    CHECK_THROWS(mat22 + mat33);
    CHECK_THROWS(mat11 + mat33);
    CHECK_THROWS(mat23 + mat32);

    // check other side
    CHECK_THROWS(mat22 + mat11);
    CHECK_THROWS(mat33 + mat22);
    CHECK_THROWS(mat33 + mat11);
    CHECK_THROWS(mat32 + mat23);
    
    /* check big matrixes */
    /* RULE 1 */
    CHECK_THROWS(bigMat1 + bigMat2);
    CHECK_THROWS(bigMat2 + bigMat3);
    CHECK_THROWS(bigMat1 + bigMat3);

    // check other side
    CHECK_THROWS(bigMat2 + bigMat1);
    CHECK_THROWS(bigMat3 + bigMat2);
    CHECK_THROWS(bigMat3 + bigMat1);

    /* check big matrixes with matrix 0*/
    /* RULE 1 */
    CHECK_THROWS(bigMat1 + mat0);
    CHECK_THROWS(bigMat2 + mat0);
    CHECK_THROWS(bigMat3 + mat0);

    // check other side
    CHECK_THROWS(mat0 + bigMat1);
    CHECK_THROWS(mat0 + bigMat2);
    CHECK_THROWS(mat0 + bigMat3);
    
    /* check big matrixes with normal matrixes */
    /* RULE 1 */
    CHECK_THROWS(bigMat3 + mat33);
    CHECK_THROWS(bigMat1 + mat11);
    CHECK_THROWS(bigMat2 + mat22);

    // check other side
    CHECK_THROWS(mat33 + bigMat3);
    CHECK_THROWS(mat11 + bigMat1);
    CHECK_THROWS(mat22 + bigMat2);


    /* check throws unary plus operator */

}

TEST_CASE("Bad input - matrix subtraction operator")
{
    
     // big vectors
    size_t bigNum1 = 250000;
    size_t bigNum2 = (size_t)(bigNum1 * 4);
    size_t bigNum3 = (size_t) (bigNum1 * 100);
    vector<double> bigVec1(bigNum1);
    vector<double> bigVec2(bigNum2);
    vector<double> bigVec3(bigNum3);
   for(size_t i=0; i< bigNum1; i++){
        bigVec1[i] = 1;
    }
    for(size_t i=0; i< bigNum2; i++){
        bigVec2[i] = 2;
    }
    for(size_t i=0; i< bigNum3; i++){
        bigVec3[i] = 3;
    }
    Matrix bigMat1(bigVec1, 500, 500);
    Matrix bigMat2(bigVec2, 1000, 1000);
    Matrix bigMat3(bigVec3, 5000, 5000);
     /* check throws subtraction operator operator */
    /* RULE 1 */
    // checking mat 0
    CHECK_THROWS(mat11 + mat0);
    CHECK_THROWS(mat22 + mat0);
    CHECK_THROWS(mat33 + mat0);
    CHECK_THROWS(mat23 + mat0);
    CHECK_THROWS(mat32 + mat0);

    // check other side
    CHECK_THROWS(mat0 + mat11);
    CHECK_THROWS(mat0 + mat22);
    CHECK_THROWS(mat0 + mat33);
    CHECK_THROWS(mat0 + mat23);
    CHECK_THROWS(mat0 + mat32);
    
    /* check normal matrixes */
    /* RULE 1 */
    CHECK_THROWS(mat11 + mat22);
    CHECK_THROWS(mat22 + mat33);
    CHECK_THROWS(mat11 + mat33);
    CHECK_THROWS(mat23 + mat32);

    // check other side
    CHECK_THROWS(mat22 - mat11);
    CHECK_THROWS(mat33 - mat22);
    CHECK_THROWS(mat33 - mat11);
    CHECK_THROWS(mat32 - mat23);
    
    /* check big matrixes */
    /* RULE 1 */
    CHECK_THROWS(bigMat1 - bigMat2);
    CHECK_THROWS(bigMat2 - bigMat3);
    CHECK_THROWS(bigMat1 - bigMat3);

    // check other side
    CHECK_THROWS(bigMat2 - bigMat1);
    CHECK_THROWS(bigMat3 - bigMat2);
    CHECK_THROWS(bigMat3 - bigMat1);

    /* check big matrixes with matrix 0*/
    /* RULE 1 */
    CHECK_THROWS(bigMat1 - mat0);
    CHECK_THROWS(bigMat2 - mat0);
    CHECK_THROWS(bigMat3 - mat0);

    // check other side
    CHECK_THROWS(mat0 - bigMat1);
    CHECK_THROWS(mat0 - bigMat2);
    CHECK_THROWS(mat0 - bigMat3);
    
    /* check big matrixes with normal matrixes */
    /* RULE 1 */
    CHECK_THROWS(bigMat3 - mat33);
    CHECK_THROWS(bigMat1 - mat11);
    CHECK_THROWS(bigMat2 - mat22);

    // check other side
    CHECK_THROWS(mat33 - bigMat3);
    CHECK_THROWS(mat11 - bigMat1);
    CHECK_THROWS(mat22 - bigMat2);
}

TEST_CASE("Bad Input - scalar subtraction operator")
{
    // checking trivial matrix throws exception when trying to subtract from it positive or negative numbers
    CHECK_THROWS(mat0 -= 5);
    CHECK_THROWS(mat0 -= -5);
    CHECK_THROWS(mat0 -= 0.5);
}
/*
TEST_CASE("Bad Input - scalar multiplication operator")
{
    


}
*/
TEST_CASE("Bad Input - matrix multiplication operator")
{
    
     // big vectors
    size_t bigNum1 = 250000;
    size_t bigNum2 = (size_t)(bigNum1 * 4);
    size_t bigNum3 = (size_t) (bigNum1 * 100);
    vector<double> bigVec1(bigNum1);
    vector<double> bigVec2(bigNum2);
    vector<double> bigVec3(bigNum3);
    for(size_t i=0; i< bigNum1; i++){
        bigVec1[i] = 1;
    }
    for(size_t i=0; i< bigNum2; i++){
        bigVec2[i] = 2;
    }
    for(size_t i=0; i< bigNum3; i++){
        bigVec3[i] = 3;
    }
    Matrix bigMat1(bigVec1, 500, 500);
    Matrix bigMat2(bigVec2, 1000, 1000);
    Matrix bigMat3(bigVec3, 5000, 5000);
    /* check left mat's column and right mat's row not equal */
    
    // normal checks
    CHECK_THROWS(mat11 * mat22);
    CHECK_THROWS(mat22 * mat33);
    CHECK_THROWS(mat11 * mat33);
    CHECK_THROWS(mat11 * mat23);
    CHECK_THROWS(mat11 * mat32);

    // other side
    CHECK_THROWS(mat22 * mat11);
    CHECK_THROWS(mat33 * mat22);
    CHECK_THROWS(mat33 * mat11);
    CHECK_THROWS(mat23 * mat11);
    CHECK_THROWS(mat32 * mat11);

    /* check big matrixes */
    CHECK_THROWS(bigMat1 * bigMat2);
    CHECK_THROWS(bigMat1 * bigMat3);
    CHECK_THROWS(bigMat2 * bigMat3);

    // other side
    CHECK_THROWS(bigMat2 * bigMat1);
    CHECK_THROWS(bigMat3 * bigMat1);
    CHECK_THROWS(bigMat3 * bigMat2);

    /* check big matrixes with normal matrixes */
    CHECK_THROWS(bigMat1 * mat11);
    CHECK_THROWS(bigMat1 * mat22);
    CHECK_THROWS(bigMat1 * mat33);
    CHECK_THROWS(bigMat2 * mat11);
    CHECK_THROWS(bigMat2 * mat22);
    CHECK_THROWS(bigMat2 * mat33);
    CHECK_THROWS(bigMat3 * mat11);
    CHECK_THROWS(bigMat3 * mat22);
    CHECK_THROWS(bigMat3 * mat33);

    // other side
    CHECK_THROWS(mat11 * bigMat1);
    CHECK_THROWS(mat22 * bigMat1);
    CHECK_THROWS(mat33 * bigMat1);
    CHECK_THROWS(mat11 * bigMat2);
    CHECK_THROWS(mat22 * bigMat2);
    CHECK_THROWS(mat33 * bigMat2);
    CHECK_THROWS(mat11 * bigMat3);
    CHECK_THROWS(mat22 * bigMat3);
    CHECK_THROWS(mat33 * bigMat3);

    // check confusion
    CHECK_THROWS(mat32 * mat33);
    CHECK_THROWS(mat22 * mat32);

}




