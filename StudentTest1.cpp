#include <iostream>
#include <stdlib.h>
#include <string>
#include "doctest.h"
#include <vector>
#include "Matrix.hpp"
#include <cmath>

using namespace std;
namespace zich{ 

const int ten = 10;

TEST_CASE("Case: Invalid multiplication and amount"){
    vector<double> identity_3 = {1,0,0,0,1,0,0,0,1};//3x3
    vector<double> vec1 = {1,1,1,1,1,1,1,1,1};//3x3
    vector<double> arr = {2,1,1,1,2,1,1,1,2};//3x3   arr = identity_3 + vec1
    vector<double> vec2 = {1,0,0,0,0,1,0,0,0,0,1,0};//3x4
    vector<double> identity_4 = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};//4x4
    Matrix mat1(identity_3,3,3);
    Matrix mat2(vec2,3,4);
    Matrix mat3(identity_4,4,4);
    Matrix mat4_arr(arr,3,3);
    CHECK_THROWS((mat2*mat1));
    CHECK_THROWS(mat3*mat2);
    CHECK_THROWS(mat2*mat2);
    CHECK_THROWS(mat4_arr*mat3);
    CHECK_THROWS(mat2*mat4_arr);
    for (double i = 0; i < 500; i++)
    {
    vector<double> arr1 = {i, i+1, i+2, i+3};//2x2
    vector<double> arr2 = {i,i,i,i,i,i,i,i,i};//3x3
    vector<double> arr = {i};//1x1
    Matrix mat1(arr1,2,2);
    Matrix mat2(arr2,3,3);
    Matrix mat(arr,1,1);
    CHECK_THROWS(mat1*mat2);
    CHECK_THROWS(mat2*mat1);
    CHECK_THROWS(mat2+mat1);  
    CHECK_THROWS(mat1+mat2);
    CHECK_THROWS(mat+mat2);
    CHECK_THROWS(mat1+mat);
    CHECK_THROWS(mat2*mat);      
    }

    for (double i = 0; i < ten; i++)
    {
    vector<double> arr1 = {i, i+1, i+2, i+3};//2x2
    for(double j=0; j<ten; j++){
    vector<double> arr2 = {j};//1x1
    Matrix mat1(arr1,2,2);
    Matrix mat2(arr2,1,1);
    CHECK_THROWS(mat2*mat1);
    CHECK_THROWS(mat1*mat2);
    }     
    }
}
TEST_CASE("Case: Invalid Subtraction matrix"){
    for (double i = 0; i < 500; i++)
    {
    vector<double> arr1 = {i, i+1, i+2, i+3};//2x2
    vector<double> arr2 = {i,i,i,i,i,i,i,i,i};//3x3
    Matrix mat1(arr1,2,2);
    Matrix mat2(arr2,3,3);
    CHECK_THROWS(mat1-mat2);
    CHECK_THROWS(mat2-mat1);  
    }
}

TEST_CASE("matrix multiplication"){
    vector<double> identity_3 = {1,0,0,0,1,0,0,0,1};//3x3
    Matrix mat_identity_3(identity_3,3,3);
    vector<double> vec1 = {1,1,1,1,1,1,1,1,1};//3x3
    vector<double> arr = {2,1,1,1,2,1,1,1,2};//3x3   arr = identity_3 + vec1
    vector<double> vec2 = {1,0,0,0,0,1,0,0,0,0,1,0};//3x4
    vector<double> identity_4 = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};//4x4
    vector<double> _vec_ = {1,1,1,1,1,1,1,1,1,1,1,1};//4x3
    Matrix _mat_(_vec_, 4, 3);
    Matrix mat1(vec1, 3,3);
    Matrix mat_arr(arr,3,3);
    Matrix mat2(vec2,3,4);
    Matrix mat_identity_4(identity_4,4,4);

    CHECK(((mat1*mat_identity_3) == mat1));
    CHECK(((mat_identity_3*mat1) == mat1));
    CHECK(((mat2*mat_identity_4) == mat2));
    CHECK(((mat1+mat_identity_3) == mat_arr));
    CHECK(((mat2*_mat_) == mat1));

    for (double i = 1; i < 500; i++)
    {
        int random = rand() % 1000;
        vector<double> vec1 = {i*random,i*random,i*random,i*random,i*random,i*random,i*random,i*random,i*random};
        Matrix matrix(vec1, 3, 3);
        CHECK(((matrix * mat_identity_3) == matrix));

        vector<double> arr1 = {i,i,i,i,i,i,i,i,i};//3x3

        vector<double> arr = {pow(i,2),pow(i,2),pow(i,2),pow(i,2),pow(i,2),pow(i,2),pow(i,2),pow(i,2),pow(i,2)};//3x3
        Matrix mat1(arr1, 3, 3);
        Matrix mat(arr, 3, 3);
        CHECK(((mat1*mat1) != mat));
        CHECK(((mat_identity_3*mat_identity_3) == mat_identity_3));
    }
}


TEST_CASE("Comparisons between matrices"){

    for (double i = 1; i < 500; i++)
    {
        vector<double> vec1 = {i,i,i,i};//2x2
        vector<double> identity_2 = {i,0,0,i};//2x2
        vector<double> vec_ = {i,i,i,i,i,i,i,i,i};//3x3
        Matrix mat(vec1,2,2);
        Matrix mat_identity_2(identity_2,2,2);
        Matrix mat_(vec_,3,3);
        CHECK((mat > mat_identity_2));
        CHECK((mat >= mat_identity_2));
        CHECK((mat != mat_identity_2));
        CHECK((mat_identity_2 < mat));
        CHECK((mat_identity_2 <= mat));

        CHECK_THROWS(bool ans = (mat < mat_));
        CHECK_THROWS(bool ans = (mat <= mat_));
        CHECK_THROWS(bool ans = (mat == mat_));
        CHECK_THROWS(bool ans = (mat >= mat_));
        CHECK_THROWS(bool ans = (mat > mat_));
        CHECK_THROWS(bool ans = (mat != mat_));

    }
}
TEST_CASE("Subtraction and amount"){
    int k=1;
    vector<double> identity_3 = {1,0,0,0,1,0,0,0,1};//3x3
    Matrix mat_identity_3(identity_3,3,3);
    int random = rand() % 1000;
    for (double i = 0; i < 500; i++)
    {
        vector<double> vec1 = {i*random,i*random,i*random,i*random,i*random,i*random,i*random,i*random,i*random};
        Matrix matrix(vec1, 3, 3);

        vector<double> vec = {i*random+k,i*random+k,i*random+k,i*random+k,i*random+k,i*random+k,i*random+k,i*random+k,i*random+k};
        Matrix mat(vec, 3, 3);

        vector<double> vec1_minus = {-i*random,-i*random,-i*random,-i*random,-i*random,-i*random,-i*random,-i*random,-i*random};
        Matrix matrix_minus(vec1_minus, 3, 3);
        
        vector<double> vec_sub = {i*random-k,i*random,i*random,i*random,i*random-k,i*random,i*random,i*random,i*random-k};
        Matrix matrix_sub(vec_sub, 3, 3);

        vector<double> vec_ = {i*random-k,i*random-k,i*random-k,i*random-k,i*random-k,i*random-k,i*random-k,i*random-k,i*random-k};
        Matrix matrix_(vec_, 3, 3);

        CHECK(((+matrix) != matrix_sub));
        CHECK(((matrix - mat_identity_3) == matrix_sub));
    }
}
TEST_CASE("CHECK ++ and -- operators"){
    int k=1;
    int random = rand() % 1000;
    for (double i = 0; i < 500; i++)
    {
        vector<double> vec1 = {i*random,i*random,i*random,i*random,i*random,i*random,i*random,i*random,i*random};
        Matrix matrix(vec1, 3, 3);

        vector<double> v = {i*random,i*random,i*random,i*random,i*random,i*random,i*random,i*random,i*random};
        Matrix matrix_v(v, 3, 3);

        vector<double> vec = {i*random+k,i*random+k,i*random+k,i*random+k,i*random+k,i*random+k,i*random+k,i*random+k,i*random+k};
        Matrix mat(vec, 3, 3);

        vector<double> vec1_minus = {-i*random,-i*random,-i*random,-i*random,-i*random,-i*random,-i*random,-i*random,-i*random};
        Matrix matrix_minus(vec1_minus, 3, 3);
        
        vector<double> vec_sub = {i*random-k,i*random,i*random,i*random,i*random-k,i*random,i*random,i*random,i*random-k};
        Matrix matrix_sub(vec_sub, 3, 3);

        vector<double> vec_ = {i*random-k,i*random-k,i*random-k,i*random-k,i*random-k,i*random-k,i*random-k,i*random-k,i*random-k};
        Matrix matrix_(vec_, 3, 3);
        CHECK(((matrix++) == matrix_v));
        CHECK(((matrix--) == mat));
        CHECK(((++matrix) == mat));
        ++matrix;
        CHECK(((--matrix) == mat));
    }
}
}
