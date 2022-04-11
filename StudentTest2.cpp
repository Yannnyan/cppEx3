#include "doctest.h"
#include "Matrix.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
using namespace zich;

std::vector<double> arr1 = {-1, 0, 0, 0, -1, 0, 0, 0, -1};
std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
std::vector<double> arr_b = {3, 0, 0, 0, 3, 0, 0, 0, 3};
std::vector<double> arr_c = {2, 0, 0, 0, 2, 0, 0, 0, 2};
std::vector<double> arr_d= {4, 0, 0, 0, 4, 0, 0, 0, 4};
std::vector<double> arr_e= {4, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0};
std::vector<double> arr_f= {5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0};
std::vector<double> arr_h= {9, 0, 0, 0, 9, 0, 0, 0, 9, 0, 0, 0};

std::vector<double> arr1_1 = {0, 1, 1, 1, 0, 1, 1, 1,0};
std::vector<double> identity_1 = {2, 1, 1, 1, 2, 1, 1, 1, 2};
std::vector<double> arr_b_1 = {4, 1, 1, 1, 4, 1, 1, 1, 4};
std::vector<double> arr_c_1 = {3, 1, 1, 1, 3, 1, 1, 1, 3};
std::vector<double> arr_d_1= {5, 1, 1, 1, 5, 1, 1, 1, 5};
std::vector<double> arr_e_1= {5, 1, 1, 1, 5, 1, 1, 1, 5, 1, 1, 1};
std::vector<double> arr_f_1= {6, 1, 1, 1, 6, 1, 1, 1, 6, 1, 1, 1};
std::vector<double> arr_h_1= {10, 1, 1,1, 10, 1, 1, 1, 10, 1, 1, 1};

Matrix mat_un{arr1,3,3};
Matrix mat1{identity,3,3};
Matrix mat2{arr_b,3,3};
Matrix mat3{arr_c,3,3};
Matrix mat4{arr_d,3,3};
Matrix mat5{arr_e,4,3};
Matrix mat6{arr_f,4,3};
Matrix mat7{arr_h,4,3};

Matrix mat_un_1{arr1_1,3,3};
Matrix mat1_1{identity_1,3,3};
Matrix mat2_2{arr_b_1,3,3};
Matrix mat3_3{arr_c_1,3,3};
Matrix mat4_4{arr_d_1,3,3};
Matrix mat5_5{arr_e_1,4,3};
Matrix mat6_6{arr_f_1,4,3};
Matrix mat7_7{arr_h_1,4,3};

std::vector<double> arr_cin = {1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1};
Matrix mat_cin{arr_cin,3,4};

bool equalto = false;

TEST_CASE("function + binary matrix and matrix"){

    CHECK_EQ(mat2,mat1+mat3);
    CHECK_EQ(mat3,mat1+mat1);
    CHECK_EQ(mat2,mat1+mat1+mat1);
    CHECK_EQ(mat4,mat1+mat1+mat1+mat1);
    CHECK_EQ(mat4,mat1+mat1+mat3);
    CHECK_EQ(mat4,mat1+mat2);
    CHECK_EQ(mat4,mat3+mat3);

    CHECK_THROWS(mat1+mat5);
    CHECK_THROWS(mat2+mat6);
    CHECK_THROWS(mat3+mat5);
    CHECK_THROWS(mat4+mat6);

    CHECK_NOTHROW(mat5+mat6);
}

TEST_CASE("function += binary matrix and matrix"){
    mat1+=mat3;
    CHECK_EQ(mat2,mat1);
    mat2+=mat1;
    mat4+=mat3;
    CHECK_EQ(mat4,mat2);
    mat1+=mat1;
    CHECK_EQ(mat1,mat2);
    mat1+= mat3;
    mat3+= mat2;
    CHECK_EQ(mat3,mat1);
    mat5+=mat6;
    CHECK_EQ(mat5,mat7);

    CHECK_THROWS(mat5+=mat4);
    CHECK_THROWS(mat6+=mat4);
    CHECK_THROWS(mat7+=mat4);
    CHECK_THROWS(mat5+=mat3);
    CHECK_THROWS(mat6+=mat3);
}

TEST_CASE("function + unary"){
    CHECK_EQ(mat1,+mat1);
}

TEST_CASE("function - binary matrix and matrix"){
    CHECK_EQ(mat2-mat4,mat1-mat3);
    CHECK_EQ(mat4,mat1-mat3+mat2);
    CHECK_EQ(mat3,mat1-mat2+mat4);
    CHECK_EQ(mat5-mat6,mat7-mat6);
    
    CHECK_THROWS(mat1-mat5);
    CHECK_THROWS(mat2-mat6);
    CHECK_THROWS(mat3-mat7);
    CHECK_THROWS(mat4-mat5-mat7);
}

TEST_CASE("function -= binary matrix and matrix"){
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};

    mat3-=mat1;
    CHECK_EQ(mat1,mat3);
    mat2-=mat3;
    mat1+=mat3;
    CHECK_EQ(mat1,mat2);
    mat4-=mat2;
    CHECK_EQ(mat4,mat2);
    mat4+=mat1;
    mat4-=mat3;
    mat3+=mat1;
    CHECK_EQ(mat4,mat3);
    mat7-=mat6;
    CHECK_EQ(mat7,mat5);

    CHECK_THROWS(mat5-=mat4);
    CHECK_THROWS(mat6-=mat4);
    CHECK_THROWS(mat7-=mat4);
    CHECK_THROWS(mat5-=mat1);
    CHECK_THROWS(mat5-=mat2);
    CHECK_THROWS(mat3-=mat7);

}

TEST_CASE("function - unary"){
    Matrix mat1{identity,3,3};
    CHECK_EQ(-mat1,mat_un);
}

TEST_CASE("function < binary"){
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};

    CHECK_EQ(true,mat1<mat2);
    CHECK_EQ(true,mat1<mat3);
    CHECK_EQ(true,mat1<mat4);
    CHECK_EQ(true,mat2<mat4);
    CHECK_EQ(true,mat3<mat2);
    CHECK_EQ(true,mat3<mat4);

    CHECK_EQ(true,mat5<mat6);
    CHECK_EQ(true,mat6<mat7);
    CHECK_EQ(true,mat5<mat7);

    CHECK_EQ(false,mat2<mat1);
    CHECK_EQ(false,mat3<mat1);
    CHECK_EQ(false,mat4<mat1);
    CHECK_EQ(false,mat4<mat2);
    CHECK_EQ(false,mat2<mat3);
    CHECK_EQ(false,mat4<mat3);

    CHECK_EQ(false,mat6<mat5);
    CHECK_EQ(false,mat7<mat6);
    CHECK_EQ(false,mat7<mat5);

    CHECK_EQ(false,mat1<mat1);
    CHECK_EQ(false,mat2<mat2);
    CHECK_EQ(false,mat3<mat3);
    CHECK_EQ(false,mat4<mat4);
    CHECK_EQ(false,mat5<mat5);
    CHECK_EQ(false,mat6<mat6);
    CHECK_EQ(false,mat7<mat7);

    CHECK_THROWS(equalto =(mat4<mat7));
    CHECK_THROWS(equalto =(mat4<mat5));
    CHECK_THROWS(equalto =(mat4<mat6));
    CHECK_THROWS(equalto =(mat1<mat7));
    CHECK_THROWS(equalto =(mat2<mat7));
    CHECK_THROWS(equalto =(mat3<mat7));
    CHECK_THROWS(equalto =(mat4<mat5));
}

TEST_CASE("function <= binary"){
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};

    CHECK_EQ(true,mat1<=mat2);
    CHECK_EQ(true,mat1<=mat3);
    CHECK_EQ(true,mat1<=mat4);
    CHECK_EQ(true,mat2<=mat4);
    CHECK_EQ(true,mat3<=mat2);
    CHECK_EQ(true,mat3<=mat4);

    CHECK_EQ(true,mat5<=mat6);
    CHECK_EQ(true,mat6<=mat7);
    CHECK_EQ(true,mat5<=mat7);

    CHECK_EQ(false,mat2<=mat1);
    CHECK_EQ(false,mat3<=mat1);
    CHECK_EQ(false,mat4<=mat1);
    CHECK_EQ(false,mat4<=mat2);
    CHECK_EQ(false,mat2<=mat3);
    CHECK_EQ(false,mat4<=mat3);

    CHECK_EQ(false,mat6<=mat5);
    CHECK_EQ(false,mat7<=mat6);
    CHECK_EQ(false,mat7<=mat5);

    CHECK_EQ(true,mat1<=mat1);
    CHECK_EQ(true,mat2<=mat2);
    CHECK_EQ(true,mat3<=mat3);
    CHECK_EQ(true,mat4<=mat4);
    CHECK_EQ(true,mat5<=mat5);
    CHECK_EQ(true,mat6<=mat6);
    CHECK_EQ(true,mat7<=mat7);

    CHECK_THROWS(equalto =(mat4<=mat7));
    CHECK_THROWS(equalto =(mat4<=mat5));
    CHECK_THROWS(equalto =(mat4<=mat6));
    CHECK_THROWS(equalto =(mat1<=mat7));
    CHECK_THROWS(equalto =(mat2<=mat7));
    CHECK_THROWS(equalto =(mat3<=mat7));
    CHECK_THROWS(equalto =(mat4<=mat5));

}

TEST_CASE("function > binary"){
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};

    CHECK_EQ(true,mat2>mat1);
    CHECK_EQ(true,mat3>mat1);
    CHECK_EQ(true,mat4>mat1);
    CHECK_EQ(true,mat4>mat2);
    CHECK_EQ(true,mat2>mat3);
    CHECK_EQ(true,mat4>mat3);

    CHECK_EQ(true,mat6>mat5);
    CHECK_EQ(true,mat7>mat6);
    CHECK_EQ(true,mat7>mat5);

    CHECK_EQ(false,mat1>mat2);
    CHECK_EQ(false,mat1>mat3);
    CHECK_EQ(false,mat1>mat4);
    CHECK_EQ(false,mat2>mat4);
    CHECK_EQ(false,mat3>mat2);
    CHECK_EQ(false,mat3>mat4);

    CHECK_EQ(false,mat5>mat6);
    CHECK_EQ(false,mat6>mat7);
    CHECK_EQ(false,mat5>mat7);

    CHECK_EQ(false,mat1>mat1);
    CHECK_EQ(false,mat2>mat2);
    CHECK_EQ(false,mat3>mat3);
    CHECK_EQ(false,mat4>mat4);
    CHECK_EQ(false,mat5>mat5);
    CHECK_EQ(false,mat6>mat6);
    CHECK_EQ(false,mat7>mat7);

    CHECK_THROWS(equalto =(mat4>mat7));
    CHECK_THROWS(equalto =(mat4>mat5));
    CHECK_THROWS(equalto =(mat4>mat6));
    CHECK_THROWS(equalto =(mat1>mat7));
    CHECK_THROWS(equalto =(mat2>mat7));
    CHECK_THROWS(equalto =(mat3>mat7));
    CHECK_THROWS(equalto =(mat4>mat5));

}

TEST_CASE("function >= binary"){
Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};

    CHECK_EQ(true,mat2>=mat1);
    CHECK_EQ(true,mat3>=mat1);
    CHECK_EQ(true,mat4>=mat1);
    CHECK_EQ(true,mat4>=mat2);
    CHECK_EQ(true,mat2>=mat3);
    CHECK_EQ(true,mat4>=mat3);

    CHECK_EQ(true,mat6>=mat5);
    CHECK_EQ(true,mat7>=mat6);
    CHECK_EQ(true,mat7>=mat5);

    CHECK_EQ(false,mat1>=mat2);
    CHECK_EQ(false,mat1>=mat3);
    CHECK_EQ(false,mat1>=mat4);
    CHECK_EQ(false,mat2>=mat4);
    CHECK_EQ(false,mat3>=mat2);
    CHECK_EQ(false,mat3>=mat4);

    CHECK_EQ(false,mat5>=mat6);
    CHECK_EQ(false,mat6>=mat7);
    CHECK_EQ(false,mat5>=mat7);

    CHECK_EQ(true,mat1>=mat1);
    CHECK_EQ(true,mat2>=mat2);
    CHECK_EQ(true,mat3>=mat3);
    CHECK_EQ(true,mat4>=mat4);
    CHECK_EQ(true,mat5>=mat5);
    CHECK_EQ(true,mat6>=mat6);
    CHECK_EQ(true,mat7>=mat7);

    CHECK_THROWS(equalto =(mat4>=mat7));
    CHECK_THROWS(equalto =(mat4>=mat5));
    CHECK_THROWS(equalto =(mat4>=mat6));
    CHECK_THROWS(equalto =(mat1>=mat7));
    CHECK_THROWS(equalto =(mat2>=mat7));
    CHECK_THROWS(equalto =(mat3>=mat7));
    CHECK_THROWS(equalto =(mat4>=mat5));
}

TEST_CASE("function == binary"){
    CHECK_EQ(false,mat1==mat2);
    CHECK_EQ(false,mat1==mat4);
    CHECK_EQ(false,mat3==mat2);
    CHECK_EQ(false,mat3==mat4);

    CHECK_EQ(true,mat1==mat1);
    CHECK_EQ(true,mat2==mat2);
    CHECK_EQ(true,mat3==mat3);
    CHECK_EQ(true,mat4==mat4);
    CHECK_EQ(true,mat5==mat5);
    CHECK_EQ(true,mat6==mat6);
    CHECK_EQ(true,mat7==mat7);

    CHECK_EQ(true,mat1==mat3);
    CHECK_EQ(true,mat2==mat4);
    CHECK_EQ(true,mat5==mat7);

    mat6++;
    CHECK_EQ(false,mat6==mat7);

    CHECK_THROWS(equalto =(mat4==mat7));
    CHECK_THROWS(equalto =(mat4==mat5));
    CHECK_THROWS(equalto =(mat4==mat6));
    CHECK_THROWS(equalto =(mat1==mat7));
    CHECK_THROWS(equalto =(mat2==mat7));
    CHECK_THROWS(equalto =(mat3==mat7));
    CHECK_THROWS(equalto =(mat4==mat5));
}

TEST_CASE("function != binary"){

    CHECK_EQ(true,mat1!=mat2);
    CHECK_EQ(true,mat1!=mat4);
    CHECK_EQ(true,mat3!=mat2);
    CHECK_EQ(true,mat3!=mat4);

    CHECK_EQ(false,mat1!=mat1);
    CHECK_EQ(false,mat2!=mat2);
    CHECK_EQ(false,mat3!=mat3);
    CHECK_EQ(false,mat4!=mat4);
    CHECK_EQ(false,mat5!=mat5);
    CHECK_EQ(false,mat6!=mat6);
    CHECK_EQ(false,mat7!=mat7);

    CHECK_EQ(false,mat1!=mat3);
    CHECK_EQ(false,mat2!=mat4);
    CHECK_EQ(false,mat5!=mat7);

    mat6++;
    CHECK_EQ(true,mat6!=mat7);

    CHECK_THROWS(equalto =(mat4!=mat7));
    CHECK_THROWS(equalto =(mat4!=mat5));
    CHECK_THROWS(equalto =(mat4!=mat6));
    CHECK_THROWS(equalto =(mat1!=mat7));
    CHECK_THROWS(equalto =(mat2!=mat7));
    CHECK_THROWS(equalto =(mat3!=mat7));
    CHECK_THROWS(equalto =(mat4!=mat5));
}

TEST_CASE("function ++ before"){
    Matrix mat_un{arr1,3,3};
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};

    ++mat_un;
    ++mat1;
    ++mat2;
    ++mat3;
    ++mat4;
    ++mat5;
    ++mat6;
    ++mat7;

    CHECK(mat_un_1 == mat_un);
    CHECK(mat1 == mat1_1);
    CHECK(mat2 == mat2_2);
    CHECK(mat3 == mat3_3);
    CHECK(mat4 == mat4_4);
    CHECK(mat5 == mat5_5);
    CHECK(mat6 == mat6_6);
    CHECK(mat7 == mat7_7);


}

TEST_CASE("function ++ after"){
    Matrix mat_un{arr1,3,3};
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};

    mat_un++;
    mat1++;
    mat2++;
    mat3++;
    mat4++;
    mat5++;
    mat6++;
    mat7++;

    CHECK(mat_un_1 == mat_un);
    CHECK(mat1 == mat1_1);
    CHECK(mat2 == mat2_2);
    CHECK(mat3 == mat3_3);
    CHECK(mat4 == mat4_4);
    CHECK(mat5 == mat5_5);
    CHECK(mat6 == mat6_6);
    CHECK(mat7 == mat7_7);
}

TEST_CASE("function -- before"){
    Matrix mat_un{arr1,3,3};
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};

    --mat_un_1;
    --mat1_1;
    --mat2_2;
    --mat3_3;
    --mat4_4;
    --mat5_5;
    --mat6_6;
    --mat7_7;

    CHECK(mat_un_1 == mat_un);
    CHECK(mat1 == mat1_1);
    CHECK(mat2 == mat2_2);
    CHECK(mat3 == mat3_3);
    CHECK(mat4 == mat4_4);
    CHECK(mat5 == mat5_5);
    CHECK(mat6 == mat6_6);
    CHECK(mat7 == mat7_7);
}

TEST_CASE("function -- after"){
    Matrix mat_un{arr1,3,3};
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};
    Matrix mat_un_1{arr1_1,3,3};
    Matrix mat1_1{identity_1,3,3};
    Matrix mat2_2{arr_b_1,3,3};
    Matrix mat3_3{arr_c_1,3,3};
    Matrix mat4_4{arr_d_1,3,3};
    Matrix mat5_5{arr_e_1,4,3};
    Matrix mat6_6{arr_f_1,4,3};
    Matrix mat7_7{arr_h_1,4,3};

    --mat_un_1;
    --mat1_1;
    --mat2_2;
    --mat3_3;
    --mat4_4;
    --mat5_5;
    --mat6_6;
    --mat7_7;

    CHECK(mat_un_1 == mat_un);
    CHECK(mat1 == mat1_1);
    CHECK(mat2 == mat2_2);
    CHECK(mat3 == mat3_3);
    CHECK(mat4 == mat4_4);
    CHECK(mat5 == mat5_5);
    CHECK(mat6 == mat6_6);
    CHECK(mat7 == mat7_7);
}

TEST_CASE("function *= matrix and than int"){
    Matrix mat_un{arr1,3,3};
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};
    mat1*=3;
    CHECK(mat1 == mat2);
    mat1-=mat3;
    mat1*=4;
    CHECK(mat4 == mat1);
    mat1-=mat2;
    mat1*=2;
    CHECK(mat3 == mat1);
    mat5*= 9;
    mat7*=4;
    CHECK(mat5 == mat7);
    mat4*=9;
    CHECK_THROWS( equalto=(mat4*5 == mat5*4));    
}

TEST_CASE("function * matrix and than int"){
    Matrix mat_un{arr1,3,3};
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};

    CHECK(mat1*3 == mat2);
    CHECK(mat1*4 == mat4);
    CHECK(mat1*2 == mat3);

    CHECK(mat5*9 == mat7*4);
    CHECK(mat6*9 == mat7*5);
    CHECK(mat5*5 == mat6*4);

    CHECK_THROWS( equalto=(mat4*45 == mat5)); 

    
}

TEST_CASE("function * matrix and matrix"){
    Matrix mat_un{arr1,3,3};
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};

    CHECK(mat2*mat1 == mat2);
    CHECK(mat4*mat1 == mat4);
    CHECK(mat3*mat1 == mat3);
    CHECK(mat3*mat2 == mat3+mat4);

    CHECK_NOTHROW(mat7*mat1);
    CHECK_NOTHROW(mat7*mat2);
    CHECK_NOTHROW(mat7*mat3);
    CHECK_NOTHROW(mat7*mat4);
    CHECK_NOTHROW(mat6*mat1);
    CHECK_NOTHROW(mat6*mat2);
    CHECK_NOTHROW(mat6*mat3);
    CHECK_NOTHROW(mat6*mat4);
    CHECK_NOTHROW(mat5*mat1);
    CHECK_NOTHROW(mat5*mat2);
    CHECK_NOTHROW(mat5*mat3);
    CHECK_NOTHROW(mat5*mat4);

    CHECK_THROWS(mat7*mat5);
    CHECK_THROWS(mat7*mat6);
    CHECK_THROWS(mat6*mat5); 
}

TEST_CASE("function *= matrix and matrix"){
    Matrix mat_un{arr1,3,3};
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};
    Matrix mat_un_1{arr1_1,3,3};
    Matrix mat1_1{identity_1,3,3};
    Matrix mat2_2{arr_b_1,3,3};
    Matrix mat3_3{arr_c_1,3,3};
    Matrix mat4_4{arr_d_1,3,3};
    Matrix mat5_5{arr_e_1,4,3};
    Matrix mat6_6{arr_f_1,4,3};
    Matrix mat7_7{arr_h_1,4,3};
    --mat_un_1;
    --mat1_1;
    --mat2_2;
    --mat3_3;
    --mat4_4;
    --mat5_5;
    --mat6_6;
    --mat7_7;
    
    mat2*=mat1;
    CHECK(mat2== mat2_2);
    mat4*=mat1;
    CHECK(mat4 == mat4_4);
    mat3*=mat1;
    CHECK(mat3 == mat3_3);
    mat2*=mat3;
    CHECK(mat2 == mat3+mat4);

    CHECK_THROWS(mat7*=mat5);
    CHECK_THROWS(mat7*=mat6);
    CHECK_THROWS(mat6*=mat5); 

    CHECK_NOTHROW(mat7*=mat1);
    CHECK_NOTHROW(mat7*=mat2);
    CHECK_NOTHROW(mat7*=mat3);
    CHECK_NOTHROW(mat7*=mat4);
    CHECK_NOTHROW(mat6*=mat1);
    CHECK_NOTHROW(mat6*=mat2);
    CHECK_NOTHROW(mat6*=mat3);
    CHECK_NOTHROW(mat6*=mat4);
    CHECK_NOTHROW(mat5*=mat1);
    CHECK_NOTHROW(mat5*=mat2);
    CHECK_NOTHROW(mat5*=mat3);
    CHECK_NOTHROW(mat5*=mat4);
}

TEST_CASE("function * int and than matrix"){
    Matrix mat_un{arr1,3,3};
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
    Matrix mat5{arr_e,4,3};
    Matrix mat6{arr_f,4,3};
    Matrix mat7{arr_h,4,3};

    CHECK(3*mat1 == mat2);
    CHECK(4*mat1 == mat4);
    CHECK(2*mat1 == mat3);

    CHECK(9*mat5 == 4*mat7);
    CHECK(9*mat6 == 5*mat7);
    CHECK(5*mat5 == 4*mat6);

    CHECK_THROWS( equalto=(45*mat4 == mat5));
}

TEST_CASE("function <<"){
    Matrix mat1{identity,3,3};
    Matrix mat2{arr_b,3,3};
    Matrix mat3{arr_c,3,3};
    Matrix mat4{arr_d,3,3};
 
    ostringstream os1;
    os1 << mat1;
    CHECK(os1.str() == "[1 0 0]\n[0 1 0]\n[0 0 1]");

    ostringstream os2;
    os2 << mat2;
    CHECK(os2.str() == "[3 0 0]\n[0 3 0]\n[0 0 3]");

    ostringstream os3;
    os3 << mat3;
    CHECK(os3.str() == "[2 0 0]\n[0 2 0]\n[0 0 2]");

    ostringstream os4;
    os4 << mat4;
    CHECK(os4.str() == "[4 0 0]\n[0 4 0]\n[0 0 4]");

    ostringstream os5;
    os5 << mat_un;
    CHECK(os5.str() == "[-1 0 0]\n[0 -1 0]\n[0 0 -1]");

}
TEST_CASE("function >>"){
    istringstream is1{"[1 1 1 1],[1 1 1 1], [1 1 1 1]\n"};
    CHECK_THROWS(is1 >> mat1);
    istringstream is2{"[1 1 1 1], [1 1 1 1] [1 1 1 1],\n"};
    CHECK_THROWS(is2 >> mat1);
    istringstream is3{"[1 11 1]  [1 1 1 1], [1 1 1 1]\n"};
    CHECK_THROWS(is3 >> mat1);
    istringstream is4{",[1 1 1 1], [1 1 1 1], [1 1 1 1]\n"};
    CHECK_THROWS(is4 >> mat1);
    istringstream is5{",,[1 1 1 1] [1 1 1 1] [1 1 1 1]\n"};
    CHECK_THROWS(is5 >> mat1);
    istringstream is6{"[ 1 1 1 1 ], [ 1 1 1 1 , [ 1 1 1 1 ]]\n"};
    CHECK_THROWS(is6 >> mat1);
    istringstream is7{"[1 1 1 1], [1 1 1 1], [1 1 1 1]\n"};
    CHECK_NOTHROW(is7 >> mat1);
}
































