#include "s21_matrix++.h"

S21Matrix::S21Matrix() {
    rows = 1;
    columns = 1;
    this->alloc_matrix(rows, columns);
}

S21Matrix::S21Matrix(int rows_, int columns_) {
    if (rows_ < 1 || columns_ < 1) {
        throw std::logic_error("Rows and columns cannot be < 1");
    }
    rows = rows_;
    columns = columns_;

    this->alloc_matrix(rows_, columns_);
}

S21Matrix::~S21Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

S21Matrix::S21Matrix(const S21Matrix& other) {
    rows = other.rows;
    columns = other.columns;
    alloc_matrix(other.rows, other.columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
    std::swap(*this, other);
}

int S21Matrix::getRows() {
    return (rows);
}

int S21Matrix::getColumns() {
    return (columns);
}

void S21Matrix::setRows(int rows_) {
    if (rows_ < 1) {
        throw std::logic_error("Rows cannot be < 1");
    }
    S21Matrix B(rows_, columns);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns; j++) {
            if (i >= rows) {
                B.matrix[i][j] = 0.0;
            } else {
                B.matrix[i][j] = matrix[i][j];
            }
        }
    }
    delete_matrix();
    matrix = B.matrix;
    rows = rows_;
    //todo nullobj
}

void S21Matrix::setCols(int cols_) {
    if (cols_ < 1) {
        throw std::logic_error("Cols cannot be < 1");
    }
    S21Matrix B(rows, cols_);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols_; j++) {
            if (j >= columns) {
                matrix[i][j] = 0.0;
            } else {
                B.matrix[i][j] = matrix[i][j];
            }
        }
    }
    delete_matrix();
    matrix = B.matrix;
    columns = cols_;
}

void S21Matrix::delete_matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void S21Matrix::alloc_matrix(int rows_, int columns_) {
    matrix = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
        matrix[i] = new double[columns_]{};
    }
}

bool S21Matrix::eq_matrix(const S21Matrix& other) {
    bool result = false;
    if (columns == other.columns && rows == other.rows) {
        for (int n = 0; n < rows; n++) {
            for (int m = 0; m < columns; m++) {
                if (fabs(matrix[n][m] - other.matrix[n][m]) >= eps) {
                    result = false;
                    break;
                }
            }
        }
    } else {
        result = false;
    }
    return result;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
    if (rows != other.rows && columns != other.columns) {
        throw std::logic_error("Rows and columns must be the same");
    }
    for (int n = 0; n < rows; n++) {
        for (int m = 0; m < columns; m++) {
            matrix[n][m] = matrix[n][m] + other.matrix[n][m];
        }
    }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
    if (rows != other.rows && columns != other.columns) {
        throw std::logic_error("Rows and columns must be the same");
    }
    for (int n = 0; n < rows; n++) {
        for (int m = 0; m < columns; m++) {
            matrix[n][m] = matrix[n][m] - other.matrix[n][m];
        }
    }
}

void S21Matrix::mul_number(const double num) {
    for (int n = 0; n < rows; n++) {
        for (int m = 0; m < columns; m++) {
            matrix[n][m] = matrix[n][m] * num;
        }
    }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
    if (columns != other.rows) {
        throw std::logic_error("Matrix multiplication logic error");
    }
    for (int n = 0; n < rows; n++) {
        for (int m = 0; m < other.columns; m++) {
            for (int k = 0; k < columns; k++) {
                matrix[n][m] += matrix[n][k] * other.matrix[k][m];
            }
        }
    }
}

S21Matrix S21Matrix::transpose() {
    S21Matrix C(columns, rows);
    for (int n = 0; n < rows; n++) {
        for (int m = 0; m < columns; m++) {
            C.matrix[m][n] = matrix[n][m];
        }
    }
    return C;
}

S21Matrix S21Matrix::calc_complements() {
    S21Matrix C(rows - 1, columns - 1);
    S21Matrix B(rows, columns);
    if (rows != columns) {
        throw std::logic_error("Matrix is not square");
    }
    for (int n = 0; n < rows; n++) {
        for (int m = 0; m < columns; m++) {
            this->get_minor_from_matrix(C, n, m); /// hz che eto blya
            B.matrix[n][m] = C.determinant() * pow(-1, n + m);
        }
    }
    return B;
}

double S21Matrix::determinant() {
    double result = 0.0;
    if (rows != columns) {
        throw std::logic_error("Matrix is not square");
    }
    for (int j = 0; j < columns; j++) {
        if (rows == 1) {
            result = matrix[0][0];
        } else if (rows == 2) {
            result = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        } else {
            S21Matrix C(rows - 1, columns - 1);
            this->get_minor_from_matrix(C, 0, j);
            result += matrix[0][j] * pow(-1, 0 + j + 2) * C.determinant();
        }
    }
    return result;
}

S21Matrix S21Matrix::inverse_matrix() {
    if (this->determinant() == 0.0) {
        throw std::logic_error(
        "\nThe number of determinant cannot be equal to 0\n");
    } else if (rows != columns) {
        throw std::logic_error("Matrix is not square");
    }
    double det = 1/this->determinant();
    S21Matrix B(this->calc_complements());
    S21Matrix C(B.transpose());
    C.mul_number(det);
    
    return C;
}

//////////// доп функции к матрицам /////////////

S21Matrix S21Matrix::get_minor_from_matrix(const S21Matrix& other, int rows_, int columns_) {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (i != rows_ && j != columns_) {
                if (i > rows_ && j > columns_) {
                    matrix[i-1][j-1] = other.matrix[i][j];
                } else if (j < columns && i < rows) {
                    matrix[i][j] = other.matrix[i][j];
                } else if (j > columns && i < rows) {
                    matrix[i][j-1] = other.matrix[i][j];
                } else if (j < columns && i > rows) {
                    matrix[i-1][j] = other.matrix[i][j];
                }
            }
        }
    }
    return *this;
}

////////////////////////////////////////////////////

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix res(*this);
    res.sum_matrix(other);
    return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix res(*this);
    res.sub_matrix(other);
    return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix res(*this);
    res.mul_matrix(other);
    return res;
}

S21Matrix S21Matrix::operator*(double num) {
    S21Matrix res(*this);
    res.mul_number(num);
    return res;
}

S21Matrix operator*(double num, const S21Matrix& other) {
    S21Matrix res(other);
    res.mul_number(num);
    return res;
}

bool S21Matrix::operator==(const S21Matrix& other) {
    return this->eq_matrix(other);
}

void S21Matrix::operator+=(const S21Matrix& other) {
    this->sum_matrix(other);
}

void S21Matrix::operator-=(const S21Matrix& other) {
    this->sub_matrix(other);
}

void S21Matrix::operator*=(const S21Matrix& other) {
    this->mul_matrix(other);
}

void S21Matrix::operator=(S21Matrix&& other) {
    std::swap(*this, other);
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows || col >= columns) {
    throw std::out_of_range("\nIndex numbers outside the matrix\n");
  }
  return this->matrix[row][col];
}

// S21Matrix A(2,4);

// S21Matrix B();

// B = std::move(A);
