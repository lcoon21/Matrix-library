#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>

constexpr double eps = 1e-7;

class S21Matrix {
 public:
    S21Matrix();
    S21Matrix(int rows_, int columns_);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    void setRows(int rows_);
    void setColumns(int columns_);
    void setMatrix(std::string path);
    int getRows();
    int getColumns();
    double** getMatrix();

    bool eq_matrix(const S21Matrix& other);
    void sum_matrix(const S21Matrix& other);
    void sub_matrix(const S21Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix& other);
    S21Matrix transpose();
    S21Matrix calc_complements();
    double determinant();
    S21Matrix inverse_matrix();

    S21Matrix get_minor_from_matrix(const S21Matrix& other, int rows_, int columns_);

    S21Matrix operator+(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix operator*(double num);
    friend S21Matrix operator*(double num, const S21Matrix& other);
    bool operator==(const S21Matrix& other);
    void operator+=(const S21Matrix& other);
    void operator-=(const S21Matrix& other);
    void operator*=(const S21Matrix& other);
    void operator*=(double num);
    void operator=(S21Matrix&& other);
    double& operator()(int row, int col);

 private:
    int rows;
    int columns;
    double** matrix;

    void delete_matrix();
    void alloc_matrix(int rows_, int columns_);
    void null_obj();
};

#endif  // SRC_S21_MATRIX_OOP_H_
