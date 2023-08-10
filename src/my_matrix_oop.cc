#include "my_matrix_oop.h"

#include <cmath>
#include <iostream>

MyMatrix::MyMatrix() {}

MyMatrix::MyMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1)
    throw std::out_of_range("Incorrect matrix proportions");
  AllocateMemory();
}

MyMatrix::MyMatrix(const MyMatrix& other) : MyMatrix(other.rows_, other.cols_) {
  CopyMatrix(other);
}

MyMatrix::MyMatrix(MyMatrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.NullifyMatrix();
}

MyMatrix::~MyMatrix() { RemoveMatrix(); }

void MyMatrix::RemoveMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) delete[] matrix_[i];
    delete[] matrix_;
  }
  NullifyMatrix();
}

void MyMatrix::NullifyMatrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

void MyMatrix::AllocateMemory() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; ++i) matrix_[i] = new double[cols_]();
}

void MyMatrix::CopyMatrix(const MyMatrix& other) {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
  }
}

void MyMatrix::PassValues(const MyMatrix& other) {
  if (matrix_) {
    int copyRows = (rows_ > other.rows_) ? other.rows_ : rows_;
    int copyCols = (cols_ > other.cols_) ? other.cols_ : cols_;
    for (int i = 0; i < copyRows; ++i)
      for (int j = 0; j < copyCols; ++j) other.matrix_[i][j] = matrix_[i][j];
  }
}

int MyMatrix::get_rows() const { return rows_; }

int MyMatrix::get_cols() const { return cols_; }

void MyMatrix::set_rows(int rows) {
  if (rows < 1) throw std::out_of_range("Incorrect rows size");
  if (rows != rows_) {
    MyMatrix result(rows, cols_);
    PassValues(result);
    *this = result;
  }
}

void MyMatrix::set_cols(int cols) {
  if (cols < 1) throw std::out_of_range("Incorrect cols size");
  if (cols != cols_) {
    MyMatrix result(rows_, cols);
    PassValues(result);
    *this = result;
  }
}

bool MyMatrix::EqMatrix(const MyMatrix& other) {
  bool status = false;
  if (this == &other) {
    status = true;
  } else if (rows_ == other.rows_ && cols_ == other.cols_ && rows_ > 0 &&
             cols_ > 0) {
    status = true;
    for (int i = 0; i < rows_ && status; ++i) {
      for (int j = 0; j < cols_ && status; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j] > 1E-05)) status = false;
      }
    }
  }
  return status;
}

void MyMatrix::SumMatrix(const MyMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("Different matrix dimensions");
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void MyMatrix::SubMatrix(const MyMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("Different matrix dimensions");
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void MyMatrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void MyMatrix::MulMatrix(const MyMatrix& other) {
  if (cols_ != other.rows_)
    throw std::out_of_range(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  MyMatrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

MyMatrix MyMatrix::Transpose() {
  MyMatrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

MyMatrix MyMatrix::Minor(int row, int col) {
  if (rows_ < 2 || cols_ < 2)
    throw std::out_of_range("Incorrect matrix proportions");
  MyMatrix result(rows_ - 1, cols_ - 1);
  for (int i = 0, res_i = 0; i < rows_; ++i) {
    if (i == row) continue;
    for (int j = 0, res_j = 0; j < cols_; ++j) {
      if (j == col) continue;
      result.matrix_[res_i][res_j] = matrix_[i][j];
      res_j++;
    }
    res_i++;
  }
  return result;
}

MyMatrix MyMatrix::CalcComplements() {
  if (rows_ != cols_) throw std::out_of_range("The matrix is not square");
  MyMatrix result(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      MyMatrix minor(Minor(i, j));
      double det = minor.Determinant();
      result.matrix_[i][j] = det * pow(-1, i + j);
    }
  }
  return result;
}

double MyMatrix::Determinant() {
  if (rows_ != cols_ || (!rows_ && !cols_))
    throw std::out_of_range("The matrix is not square, or is empty");
  double result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]);
  } else {
    for (int x = 0; x < rows_; x++) {
      MyMatrix minor(Minor(0, x));
      int sign = (x % 2) ? -1 : 1;
      result += sign * matrix_[0][x] * minor.Determinant();
    }
  }
  return result;
}

MyMatrix MyMatrix::InverseMatrix() {
  double det = Determinant();
  if (!det) throw std::out_of_range("Matrix determinant is 0");
  MyMatrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = pow(matrix_[0][0], -1);
  } else {
    result = CalcComplements().Transpose();
    result.MulNumber(1 / det);
  }
  return result;
}

MyMatrix MyMatrix::operator+(const MyMatrix& other) {
  MyMatrix result(*this);
  result.SumMatrix(other);
  return result;
}

MyMatrix MyMatrix::operator-(const MyMatrix& other) {
  MyMatrix result(*this);
  result.SubMatrix(other);
  return result;
}

MyMatrix MyMatrix::operator*(const MyMatrix& other) {
  MyMatrix result(*this);
  result.MulMatrix(other);
  return result;
}

MyMatrix MyMatrix::operator*(const double num) {
  MyMatrix result(*this);
  result.MulNumber(num);
  return result;
}

bool MyMatrix::operator==(const MyMatrix& other) { return EqMatrix(other); }

MyMatrix& MyMatrix::operator=(const MyMatrix& other) {
  if (this != &other) {
    RemoveMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocateMemory();
    CopyMatrix(other);
  }
  return *this;
}

MyMatrix& MyMatrix::operator=(MyMatrix&& other) noexcept {
  if (this != &other) {
    RemoveMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.NullifyMatrix();
  }
  return *this;
}

MyMatrix& MyMatrix::operator+=(const MyMatrix& other) {
  SumMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator-=(const MyMatrix& other) {
  SubMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator*=(const MyMatrix& other) {
  MulMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double MyMatrix::operator()(int i, int j) const {
  if (i < 0 || j < 0 || i > rows_ - 1 || j > cols_ - 1)
    throw std::out_of_range("Incorrect indexes of a matrix");
  return matrix_[i][j];
}

double& MyMatrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i > rows_ - 1 || j > cols_ - 1)
    throw std::out_of_range("Incorrect indexes of a matrix");
  return matrix_[i][j];
}